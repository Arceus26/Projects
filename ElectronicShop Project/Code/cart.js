const CartItems = document.querySelector(".cart-items");
const clearCartButton = document.getElementById("Buy_all");

let cartTotal = 0;

function displayCartItems() {
  CartItems.innerHTML = '';
  const items = JSON.parse(sessionStorage.getItem("cart"));
  cartTotal = 0;

  items.forEach((item) => {
    const cartItem = document.createElement("div");
    cartItem.className = "cart_item";
    cartItem.innerHTML = `
      <h5 class="cart_id">${item.id}</h5>
      <h5 class="cart_title">${item.title}</h5>
      <img src="${item.image}" alt="${item.title}" class="cart_img" />
      <h5 class="cart_price">$${item.price}</h5>
      <p button class="remove-button" data-id="${item.id}" onclick="removeCartItem('${item.id}')">Șterge</button></p>
    `;

    const price = parseFloat(item.price.replace('$', ''));
    cartTotal += price;

    CartItems.appendChild(cartItem);
  });

  updateTotalDisplay();
}

function updateTotalDisplay() {
  document.getElementById("total").textContent = "Total: " + cartTotal.toFixed(2) + " $";
}

function clearCart() {
  sessionStorage.removeItem("cart");
  CartItems.innerHTML = "";
  cartTotal = 0;
  updateTotalDisplay();
}

function removeCartItem(itemId) {
  const items = JSON.parse(sessionStorage.getItem('cart'));
  const indexToRemove = items.findIndex((item) => item.id === itemId);
  if (indexToRemove !== -1) {
    const removedItem = items[indexToRemove];
    const removedPrice = parseFloat(removedItem.price.replace('$', ''));
    items.splice(indexToRemove, 1);
    sessionStorage.setItem('cart', JSON.stringify(items));
    displayCartItems();
  }
}

clearCartButton.addEventListener("click", clearCart);
displayCartItems();
