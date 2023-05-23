console.log("Hello there!");

let mouse = {
    x: 0,
    y: 0
}

window.addEventListener("mousemove", event => {
    mouse.x = event.clientX;
    mouse.y = event.clientY;
})

document.addEventListener("keydown", event => {
    if (event.key === "s" && event.altKey) {
        const active = document.activeElement;
        const input = document.createElement("input");
        input.addEventListener("keypress", event => {
            if (event.key === "Enter") {
                event.preventDefault();
                navigator.clipboard.writeText(eval(input.value));
                input.remove();
                active?.focus();
            }
        })
        input.style.position = "fixed";
        input.style.left = mouse.x + "px";
        input.style.top = mouse.y + "px";
        document.body.appendChild(input);
        input.focus();
    }
})