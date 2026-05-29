// Premium Web Features for aj4y Documentation & Blog

// Material for MkDocs official subscription hook (runs on DOMContentLoaded & instant navigation)
if (typeof document$ !== "undefined") {
  document$.subscribe(function () {
    initializeSite();
  });
} else {
  document.addEventListener("DOMContentLoaded", function () {
    initializeSite();
  });
}

function initializeSite() {
  console.log("%c🚀 AJ4Y Premium Site Loaded successfully!", "color: #009688; font-weight: bold; font-size: 1.1rem;");

  // Dynamic content fading
  const mainContent = document.querySelector(".md-content");
  if (mainContent) {
    mainContent.style.opacity = 0;
    mainContent.style.transition = "opacity 0.4s ease-in-out";
    setTimeout(() => {
      mainContent.style.opacity = 1;
    }, 50);
  }

  // Setup Blog 3-column layout grid & Search/Filter
  setupBlogLayoutAndFilters();
}

function setupBlogLayoutAndFilters() {
  const searchInput = document.getElementById("blog-search");
  const filterBtns = document.querySelectorAll(".category-filters .filter-btn");
  const posts = document.querySelectorAll(".md-post--excerpt");
  const noPostsEl = document.getElementById("no-posts-found");

  // 1. Wrap posts in a 3-column grid container if not already wrapped
  if (posts.length > 0) {
    let listContainer = document.querySelector(".md-post-list");
    if (!listContainer) {
      listContainer = document.createElement("div");
      listContainer.className = "md-post-list";
      posts[0].parentNode.insertBefore(listContainer, posts[0]);
    }
    posts.forEach(post => {
      listContainer.appendChild(post);
    });
  }

  if (!searchInput || posts.length === 0) return;

  // Prevent duplicate event listener bindings
  if (searchInput.dataset.bound) return;
  searchInput.dataset.bound = "true";

  // Compute counts for each category based on posts
  const counts = { all: posts.length, Security: 0, ECE: 0, Projects: 0 };
  posts.forEach(post => {
    const meta = post.querySelector(".md-post__meta") ? post.querySelector(".md-post__meta").innerText : "";
    if (meta.includes("Security")) counts.Security++;
    if (meta.includes("ECE")) counts.ECE++;
    if (meta.includes("Projects")) counts.Projects++;
  });

  // Update button texts with beautiful badge counts
  filterBtns.forEach(btn => {
    const cat = btn.getAttribute("data-category");
    if (cat === "all") {
      btn.innerHTML = `All <span class="filter-badge">${counts.all}</span>`;
    } else if (counts[cat] !== undefined) {
      btn.innerHTML = `${cat} <span class="filter-badge">${counts[cat]}</span>`;
    }
  });

  // Filter function
  function applyFilters() {
    const query = searchInput.value.toLowerCase().trim();
    const activeBtn = document.querySelector(".category-filters .filter-btn.active");
    const activeCategory = activeBtn ? activeBtn.getAttribute("data-category") : "all";
    let visibleCount = 0;

    posts.forEach(post => {
      const title = post.querySelector(".md-post__header") ? post.querySelector(".md-post__header").innerText.toLowerCase() : "";
      const content = post.querySelector(".md-post__content") ? post.querySelector(".md-post__content").innerText.toLowerCase() : "";
      const meta = post.querySelector(".md-post__meta") ? post.querySelector(".md-post__meta").innerText : "";
      
      const matchesQuery = title.includes(query) || content.includes(query);
      const matchesCategory = activeCategory === "all" || meta.includes(activeCategory);

      if (matchesQuery && matchesCategory) {
        post.style.display = "flex";
        visibleCount++;
      } else {
        post.style.display = "none";
      }
    });

    if (noPostsEl) {
      noPostsEl.style.display = visibleCount === 0 ? "block" : "none";
    }
  }

  // Attach search listeners
  searchInput.addEventListener("input", applyFilters);

  // Attach button listeners
  filterBtns.forEach(btn => {
    btn.addEventListener("click", function() {
      filterBtns.forEach(b => b.classList.remove("active"));
      this.classList.add("active");
      applyFilters();
    });
  });

  // Run filter once to initialize
  applyFilters();
}
