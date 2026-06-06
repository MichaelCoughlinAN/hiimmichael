/**
 * homelab-dash — config.js
 * ─────────────────────────────────────────────────────────────────────────────
 * This is the only file you need to edit.
 * Both index.html and bookmarks.html read from CONFIG at runtime.
 * ─────────────────────────────────────────────────────────────────────────────
 */

const CONFIG = {

  // ── Identity ─────────────────────────────────────────────────────────────
  name: "Your Name",

  // Hero headline — rendered as: <first> <em>second</em>
  title: ["Home", "Base"],

  // Weather + clock location
  location: {
    label: "City, ST",         // displayed in the weather strip
    lat:    0.0000,            // decimal latitude  — e.g. 44.9778
    lon:   -0.0000,            // decimal longitude — e.g. -93.2650
    tz:    "America/Chicago",  // IANA timezone     — e.g. "Europe/London"
  },

  // ── Services ─────────────────────────────────────────────────────────────
  // Add or remove entries freely. The grid expands automatically.
  // icon  : any emoji
  // url   : full URL the card links to
  // meta  : short label shown under the name (usually host:port)
  services: [
    { name: "Nextcloud",   icon: "☁️",  url: "http://your-server:8085",              meta: "your-server:8085"   },
    { name: "Plex",        icon: "🎬",  url: "http://your-server:32400",             meta: "your-server:32400"  },
    { name: "Portainer",   icon: "🐳",  url: "http://your-server:9000",              meta: "your-server:9000"   },
    { name: "GitLab",      icon: "🦊",  url: "http://your-server/users/me/projects", meta: "your-server"        },
    { name: "Jenkins",     icon: "⚙️",  url: "http://your-server:8082",              meta: "your-server:8082"   },
    { name: "Code Server", icon: "💻",  url: "http://your-server:8443",              meta: "your-server:8443"   },
    { name: "Dozzle",      icon: "📋",  url: "http://your-server:8888",              meta: "your-server:8888"   },
    { name: "NetAlertX",   icon: "🔍",  url: "http://your-server:20211",             meta: "your-server:20211"  },
  ],

  // ── Bookmarks ─────────────────────────────────────────────────────────────
  // These are the "built-in" bookmarks on bookmarks.html.
  // Users can also add personal bookmarks via the UI (stored in localStorage).
  // tags : optional array — enables tag-filter chips
  bookmarks: [
    { name: "GitHub",        url: "https://github.com",            tags: ["dev"]               },
    { name: "MDN Web Docs",  url: "https://developer.mozilla.org", tags: ["dev", "reference"]  },
    { name: "Hacker News",   url: "https://news.ycombinator.com",  tags: ["news"]              },
    { name: "Docker Hub",    url: "https://hub.docker.com",        tags: ["dev", "docker"]     },
    { name: "Awesome Self-Hosted", url: "https://github.com/awesome-selfhosted/awesome-selfhosted", tags: ["reference"] },
  ],

  // ── Greetings ─────────────────────────────────────────────────────────────
  // {name} is replaced with config.name at runtime.
  // Add as many lines as you like to each pool.
  greetings: {
    morning: [
      "Good morning, {name} ☀️",
      "Rise and shine ☀️",
      "Morning, boss ☕",
      "Early bird, huh? ☕",
      "Top of the morning 🌅",
    ],
    afternoon: [
      "Welcome back, {name} 👋",
      "There they are 😎",
      "Look who showed up 😄",
      "Back at it 💪",
      "The legend returns 🫡",
    ],
    evening: [
      "Still at it, {name}? 🌙",
      "Burning the midnight oil 🕯️",
      "Evening, boss 🌆",
      "Late night session? 🌙",
      "Night owl mode 🦉",
    ],
    weekend: [
      "Weekend mode 🛋️",
      "No rest for the wicked 😅",
      "Shouldn't you be relaxing? 😄",
      "Weekend grind, respect 💪",
    ],
  },

};
