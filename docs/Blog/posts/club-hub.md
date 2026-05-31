---
date: 2026-05-29
slug: club-hub
categories:
  - Projects
tags:
  - Next.js
  - Supabase
  - Real-time
authors:
  - aj4y
hide:
  - navigation
---

# Building GFG Club Hub: The Decentralized Campus Node 🌐

![Club Hub Cover](../../assets/covers/club-hub.png)

Campus organization is often a chaotic mess of scattered Google Forms, unorganized WhatsApp groups, and spreadsheets that are permanently out of sync. To resolve this manual workload once and for all, my team **Dash Dominators** built **Club Hub**—a next-generation decentralized campus event, project registry, and leaderboard ecosystem for GeeksforGeeks campus club.

In this deep dive, we will explore the real-time node architecture, database schema, frontend styling system, and security design that made Club Hub the winning campus scaling engine at our GeeksforGeeks hackathon.

<!-- more -->

---
<a href="https://github.com/ajax-y/jdbf" class="github-card" target="_blank" rel="noopener"><div class="github-card-content"><div class="github-card-icon">📁</div><div class="github-card-info"><h4>ajax-y/jdbf</h4><p>Club Hub: Next-generation real-time campus node ecosystem built using Next.js 15, Supabase Postgres, Tailwind, and Framer Motion.</p></div></div><div class="github-card-action">View on GitHub ➔</div></a>
---

## 💡 The Core Vision: An Interactive Campus Engine

Club Hub operates on a physical-meets-digital "Node" concept. Rather than functioning as a boring administrative records system, it acts as a **living hub** built on five core pillars:

```
                  ┌─────────────────────────────────────────┐
                  │          CLUB HUB EVENT NODE            │
                  └────────────┬────────────────────────────┘
                               │
         ┌─────────────────────┼─────────────────────┐
         ▼                     ▼                     ▼
┌─────────────────┐   ┌─────────────────┐   ┌─────────────────┐
│ Live QR Ingress │   │ Hall of Fame    │   │ Live Wall Stream│
│ Merit Points    │   │ Bronze -> Diam. │   │ Projector UI    │
└─────────────────┘   └─────────────────┘   └─────────────────┘
```

1.  **The Live Node Scanner (Ingress):** Secure QR-based check-in system. Upon successful scan, members instantly receive 10 Merit Points, updating their global rank dynamically.
2.  **The Innovation Gallery (Projects):** A decentralized home for every club project, supporting real-time likes, feedback comments, and tech stack sorting tags.
3.  **Real-Time Hall of Fame (Leaderboards):** A global scrolling feed displaying all student activity, with automatic tier progressions (Bronze → Silver → Gold → Diamond).
4.  **The Live Wall (Projector View):** A high-performance broadcast layout for organizers to project onto walls, displaying real-time attendance graphs and participant cards as they scan in.
5.  **Administrative Control Board:** Toggles event nodes active/inactive, sends global system notifications, and generates event entry tokens.

---

## 🛠️ The Architecture & Technology Stack

To achieve instant, low-latency updates for large student crowds, we chose premium, industry-standard tools:

| Technical Layer | Choice | Key Rationale |
| :--- | :--- | :--- |
| **Frontend Framework** | **Next.js 15+ (App Router)** | For lightning-fast page loading speeds and highly structured routing patterns. |
| **Type Safety** | **TypeScript** | Ensuring type safety and reliable communication between the client and database. |
| **Database Engine** | **PostgreSQL (Supabase)** | Offers robust relational data mapping, low-latency queries, and native WebSocket triggers. |
| **Theme & Layout** | **Tailwind CSS** | Custom styling system using matrix-inspired cyber-slate dark elements. |
| **Micro-Animations** | **Framer Motion** | Controls layout transitions, glowing gradient headers, and sparkling canvas tails. |

---

## 🗄️ Database Design & Real-Time Sync Logic

At the core of Club Hub's real-time updating dashboard is the relational Supabase PostgreSQL engine. Here is a simplified look at the database tables we designed:

```sql
-- Profiles table tracking student merit points and global rank tiers
CREATE TABLE profiles (
  id UUID PRIMARY KEY REFERENCES auth.users,
  full_name VARCHAR(100) NOT NULL,
  merit_points INT DEFAULT 0 CHECK (merit_points >= 0),
  tier VARCHAR(20) DEFAULT 'Bronze',
  avatar_url TEXT,
  updated_at TIMESTAMP WITH TIME ZONE DEFAULT TIMEZONE('utc'::text, NOW())
);

-- Event Nodes table tracking individual check-in systems
CREATE TABLE event_nodes (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  event_name VARCHAR(150) NOT NULL,
  node_secret VARCHAR(64) UNIQUE NOT NULL, -- QR verification hash
  is_active BOOLEAN DEFAULT true,
  capacity INT,
  created_at TIMESTAMP WITH TIME ZONE DEFAULT TIMEZONE('utc'::text, NOW())
);

-- Attendance ledger connecting Profiles to Event Nodes
CREATE TABLE event_ingress (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  profile_id UUID REFERENCES profiles(id) ON DELETE CASCADE,
  node_id UUID REFERENCES event_nodes(id) ON DELETE CASCADE,
  scanned_at TIMESTAMP WITH TIME ZONE DEFAULT TIMEZONE('utc'::text, NOW()),
  UNIQUE(profile_id, node_id)
);
```

### The Real-Time Synchronization Flow
Instead of polling the server every few seconds (which drains device battery and slows servers), we set up standard PostgreSQL triggers inside Supabase that broadcast updates over WebSockets:

```
Student Scans QR Code
  ├─► Inserts Row to 'event_ingress'
  ├─► Postgres Trigger Fires
  │     ├─► Adds 10 Merit Points to Student's 'profiles' row
  │     └─► Broadcasts 'NEW_INGRESS' payload via WebSockets
  └─► Live Wall Projector UI catches event and updates dynamically!
```

---

## 🎨 Premium Visual Elements & Tailwind Configurations

To give Club Hub an immersive gaming-inspired look, we developed a detailed design system:
- **Glassmorphism CSS:** Semi-transparent cards utilizing Tailwind's `backdrop-blur-md` and `bg-slate-900/80` overlays.
- **Sparkle Engine:** A lightweight HTML5 canvas tracker that spawns particles following your mouse pointer across active dashboards.
- **Dynamic Leaderboard Scroll:** A vertical scrolling list styled to slide newly calculated entries up smoothly using CSS Keyframe animations.

---

## 🚦 Getting Started Locally

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/ajax-y/jdbf.git
    cd jdbf
    ```
2.  **Environment Variables (`.env.local`):**
    ```env
    NEXT_PUBLIC_SUPABASE_URL=your_supabase_url_placeholder
    NEXT_PUBLIC_SUPABASE_ANON_KEY=your_supabase_anonymous_key_placeholder
    ```
3.  **Database Migration:** Apply the provided `supabase_setup.sql` script inside your Supabase dashboard SQL editor to create the required profiles, nodes, and triggers.
4.  **Start the Local Server:**
    ```bash
    npm install
    npm run dev
    ```

Club Hub shows how standard administrative campus applications can be elevated into premium, highly interactive systems by combining fast databases with beautiful frontends!
