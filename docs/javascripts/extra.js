// Premium Web Features for aj4y Documentation & Blog

document.addEventListener("DOMContentLoaded", function () {
  initializeSite();
});

// MkDocs Instant loading compatible re-initialization
if (typeof app$ !== "undefined") {
  app$.subscribe(function () {
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
}
