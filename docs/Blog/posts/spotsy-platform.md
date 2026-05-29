---
date: 2026-05-29
slug: spotsy-platform
categories:
  - Projects
tags:
  - Flutter
  - Spring Boot
  - WebSockets
authors:
  - aj4y
hide:
  - navigation
---

# Designing Spotsy: A Real-Time Parking Space Booking Ecosystem 🅿️

In fast-growing metropolitan centers, finding parking is one of the most frustrating bottlenecks of daily commuting. Drivers waste fuel and crowd city roads driving in circles. To solve this challenge, I designed **Spotsy**—a high-performance, real-time parking spot reservation ecosystem inspired by modern ride-hailing services.

In this comprehensive architecture deep dive, we will explore the dual-app Flutter configuration, the Spring Boot WebSocket backend, PostgreSQL table schema models, and secure BillDesk payment integrations.

<!-- more -->

---
<div style="display: grid; grid-template-columns: repeat(auto-fit, minmax(280px, 1fr)); gap: 1rem; margin: 2rem 0;"><a href="https://github.com/ajax-y/spotsy-captain" class="github-card" style="margin: 0 !important;" target="_blank" rel="noopener"><div class="github-card-content"><div class="github-card-icon">📁</div><div class="github-card-info"><h4>spotsy-captain</h4><p>Owner app built with Flutter and Riverpod. Manage listings, accept incoming parking reservations, and track active earnings.</p></div></div></a><a href="https://github.com/ajax-y/spotsy-user" class="github-card" style="margin: 0 !important;" target="_blank" rel="noopener"><div class="github-card-content"><div class="github-card-icon">📁</div><div class="github-card-info"><h4>spotsy-user</h4><p>Driver app built with Flutter and OpenStreetMap. Scan nearby spaces, filter EV charge points, reserve, check out, and pay.</p></div></div></a></div>
---

## 🏗️ The System Architecture: Three-Tier Blueprint

Spotsy operates as a complete three-tier platform consisting of two separate mobile apps communicating with a shared backend server:

```
┌────────────────────────┐         ┌────────────────────────┐
│  Spotsy User App       │         │  Spotsy Captain App    │
│  (Flutter - Driver)    │         │  (Flutter - Space Owner)│
└───────────┬────────────┘         └───────────┬────────────┘
            │                                  │
            └─────────► [ WebSockets & REST ] ◄┘
                                │
                                ▼
                   ┌────────────────────────┐
                   │   Spring Boot Backend  │
                   │   & PostgreSQL DB      │
                   └────────────────────────┘
```

1.  **Spotsy User App (Flutter):** For drivers to scan, filter, reserve, pay, and navigate to parking slots.
2.  **Spotsy Captain App (Flutter):** For space owners to list driveways or commercial spaces, approve requests, and manage earnings.
3.  **Spotsy Backend (Spring Boot 3.x + PostgreSQL):** Manages user session tokens, processes real-time WebSocket payloads, and processes payment gateways.

---

## 🛠️ The Technical Stack At a Glance

| Layer | Component | Technical Role |
| :--- | :--- | :--- |
| **Mobile Client** | **Flutter 3.x** | Controls multi-platform Android, iOS, and Web deployment. |
| **State Management** | **Riverpod** | Ensures robust, reactive, and easily testable state maps across apps. |
| **Map Rendering** | **OpenStreetMap** | Native maps rendering via `flutter_map` (fully free & open-source). |
| **Geolocation** | **`geolocator` + `location`** | Accurately streams user latitude and longitude GPS arrays. |
| **Backend Framework**| **Spring Boot 3.x** | Powering high-performance Java REST APIs & STOMP WebSockets. |
| **Relational Database**| **PostgreSQL** | Stores profiles, vehicles, and payment ledgers securely. |

---

## 🗄️ Database Schema Design (PostgreSQL models)

To support secure financial transactions, KYC storage, and active booking queues, we designed a highly robust database layout:

```sql
-- Main Users Table holding security details and KYC verification states
CREATE TABLE users (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  phone_number VARCHAR(15) UNIQUE NOT NULL,
  email VARCHAR(100) UNIQUE,
  first_name VARCHAR(50) NOT NULL,
  last_name VARCHAR(50),
  aadhar_number_encrypted TEXT, -- Stored securely under AES-256
  kyc_status VARCHAR(20) DEFAULT 'PENDING',
  created_at TIMESTAMP WITHOUT TIME ZONE DEFAULT NOW()
);

-- User registered vehicles mapping Ev support
CREATE TABLE user_vehicles (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  user_id UUID REFERENCES users(id) ON DELETE CASCADE,
  vehicle_type VARCHAR(10) CHECK (vehicle_type IN ('BIKE', 'CAR', 'SUV')),
  registration_number VARCHAR(20) NOT NULL,
  vehicle_name VARCHAR(50),
  is_ev BOOLEAN DEFAULT false
);

-- Parking Space Registries mapped to Captains
CREATE TABLE parking_spaces (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  owner_id UUID REFERENCES users(id) ON DELETE CASCADE,
  space_name VARCHAR(150) NOT NULL,
  address TEXT NOT NULL,
  latitude DECIMAL(10, 8) NOT NULL,
  longitude DECIMAL(11, 8) NOT NULL,
  total_spaces INT NOT NULL,
  available_spaces INT NOT NULL,
  price_per_hour DECIMAL(10, 2) NOT NULL,
  has_ev_charging BOOLEAN DEFAULT false,
  is_active BOOLEAN DEFAULT true
);

-- Bookings ledger mapping transaction values
CREATE TABLE bookings (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  user_id UUID REFERENCES users(id),
  parking_space_id UUID REFERENCES parking_spaces(id),
  vehicle_id UUID REFERENCES user_vehicles(id),
  booking_status VARCHAR(40) DEFAULT 'PENDING_OWNER_CONFIRMATION',
  check_in_time TIMESTAMP,
  check_out_time TIMESTAMP,
  total_amount DECIMAL(10, 2),
  payment_status VARCHAR(20) DEFAULT 'PENDING'
);
```

---

## 🔄 The Real-Time Booking & Location Loop

Rather than relying on classic refresh screens, Spotsy manages user journeys using full-duplex WebSockets.

### 1. The Booking Request Flow
```
User App                           Spring Boot API                     Captain App
   │                                     │                                  │
   ├─► Sends WebSockets BOOKING ────────►│                                  │
   │   (/app/booking/request)            ├─► Push STOMP notification ──────►│
   │                                     │   (/topic/owner/bookings)        │
   │                                     │                                  │
   │                                     │◄─ Owner Taps ACCEPT ─────────────┤
   │                                     │   (/app/booking/accept)          │
   │◄─ Confirmed Toast Received ─────────┤                                  │
   │   (/topic/user/bookings)            │                                  │
```

### 2. Live Driver Location Tracking
Once a booking is confirmed, the driver’s app starts streaming raw GPS coordinates:
- **Driver -> STOMP Channel:** `/app/booking/{id}/location`
- **Spring Boot -> Captain Topic:** `/topic/booking/{id}/user-location`

This allows the Captain (space owner) to look at their dashboard map and see the driver's real-time vehicle movement approaching the garage!

---

## 💳 Secure BillDesk Payment Integration Flow

To ensure secure checkout, we integrated a full digital transaction model:

1.  **Initiation:** When the Captain approves the booking request, the driver taps **"Proceed to Payment"**. The client calls the REST endpoint:
    `POST /api/bookings/{id}/payment`
2.  **Order Generation:** The Spring Boot backend connects to BillDesk APIs and returns a cryptographic checkout token.
3.  **Gateway Checkout:** The mobile app opens the integrated web-view overlay allowing the user to pay safely using cards, UPI, or wallets.
4.  **Webhook Handshake:** Upon completion, BillDesk notifies our backend at:
    `POST /api/payments/webhook`
5.  **Validation:** The backend validates the payment signature, marks the booking as `COMPLETED`, updates the Captain's ledger, and triggers a real-time WebSocket toast back to the mobile app.

---

## 🛡️ Critical Security Configurations

Spotsy prioritizes data protection at every level of the database and transit systems:
*   **Encrypted Aadhaar & Bank Details:** Raw personal identification numbers are encrypted under AES-256 standard encryption keys before saving to PostgreSQL.
*   **JWT Security Lifecycles:** REST endpoints are protected with standard JSON Web Tokens. Access tokens expire after 15 minutes, with highly secure Refresh tokens running a 7-day slide cycle.

Spotsy demonstrates how combining robust mobile frontends with modern reactive backend ecosystems completely transforms regular urban commuting!
