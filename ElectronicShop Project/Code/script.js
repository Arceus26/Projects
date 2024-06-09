const AddToCart = document.querySelectorAll(".addB");

AddToCart.forEach((button) => {
  button.addEventListener("click", () => {
    const id = button.getAttribute("data-id");
    const title = button.getAttribute("data-title");
    const image = button.getAttribute("data-image");
    const price = button.getAttribute("data-price");

    const cartItem = { id, title, image, price };
    const cart = JSON.parse(sessionStorage.getItem("cart")) || [];
    cart.push(cartItem);
    sessionStorage.setItem("cart", JSON.stringify(cart));
  });
});