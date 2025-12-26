const canvas = document.getElementById('snow-canvas');
const ctx = canvas.getContext('2d');

let width, height;
let snowflakes = [];
let mouse = { x: null, y: null };

function resize() {
  width = canvas.width = window.innerWidth;
  height = canvas.height = window.innerHeight;
}
window.addEventListener('resize', resize);
resize();

canvas.addEventListener('mousemove', e => {
  mouse.x = e.clientX;
  mouse.y = e.clientY;
});
canvas.addEventListener('mouseleave', () => {
  mouse.x = null;
  mouse.y = null;
});

class Snowflake {
  constructor(layer = 1) {
    this.reset(layer);
  }

  reset(layer = 1) {
    this.x = Math.random() * width;
    this.y = Math.random() * -height;
    this.radius = Math.random() * (2 / layer) + 1;
    this.speedY = Math.random() * 1.5 * layer + 0.5;
    this.speedX = Math.random() * 0.6 - 0.3;
    this.opacity = Math.random() * 0.5 + 0.5;
    this.layer = layer;
  }

  update() {
    // Normal fall
    this.y += this.speedY;
    this.x += this.speedX + Math.sin(this.y * 0.01) * 0.5;

    // Dramatic swirl effect
    if (mouse.x !== null && mouse.y !== null) {
      const dx = mouse.x - this.x;
      const dy = mouse.y - this.y;
      const dist = Math.sqrt(dx * dx + dy * dy);

      if (dist < 200) {
        const force = (1 - dist / 200) * 0.15;
        const angle = Math.atan2(dy, dx) + Math.PI / 2;

        this.x += Math.cos(angle) * force * 15;
        this.y += Math.sin(angle) * force * 15;
      }
    }

    if (this.y > height) {
      this.reset(this.layer);
      this.y = 0;
    }

    if (this.x > width || this.x < 0) {
      this.x = (this.x + width) % width;
    }
  }

  draw() {
    ctx.beginPath();
    ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2);
    ctx.fillStyle = `rgba(255, 255, 255, ${this.opacity})`;
    ctx.fill();
  }
}

function createSnowflakes(count, layer = 1) {
  for (let i = 0; i < count; i++) {
    snowflakes.push(new Snowflake(layer));
  }
}

createSnowflakes(100, 1);
createSnowflakes(50, 2);
createSnowflakes(25, 3);

function animate() {
  ctx.clearRect(0, 0, width, height);
  for (let flake of snowflakes) {
    flake.update();
    flake.draw();
  }
  requestAnimationFrame(animate);
}

animate();