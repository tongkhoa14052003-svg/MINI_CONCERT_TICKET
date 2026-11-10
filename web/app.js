
// ============================================
// MINI CONCERT TICKET - APP.JS
// Website bán vé ca nhạc
// Thanh toán QR mô phỏng
// ============================================

// DANH SÁCH SẢN PHẨM
const products = [
    {
        id: 100001,
        name: "Đêm Nhạc Thanh Xuân",
        type: "Vé thường",
        price: 350000,
        stock: 100,
        rating: 4.8,
        emoji: "🎤"
    },
    {
        id: 100002,
        name: "Live Concert Mùa Hè",
        type: "Vé VIP",
        price: 850000,
        stock: 50,
        rating: 4.9,
        emoji: "🎸"
    },
    {
        id: 100003,
        name: "The Music Festival",
        type: "Vé thường",
        price: 450000,
        stock: 120,
        rating: 4.7,
        emoji: "🎵"
    },
    {
        id: 100004,
        name: "Đại Nhạc Hội Ánh Sáng",
        type: "Vé VIP",
        price: 1200000,
        stock: 40,
        rating: 5.0,
        emoji: "✨"
    },
    {
        id: 100005,
        name: "Acoustic Night",
        type: "Vé thường",
        price: 250000,
        stock: 80,
        rating: 4.6,
        emoji: "🎼"
    },
    {
        id: 100006,
        name: "Summer Sound Festival",
        type: "Vé VIP",
        price: 950000,
        stock: 60,
        rating: 4.9,
        emoji: "🎧"
    },
    {
        id: 100007,
        name: "Concert Giai Điệu Việt",
        type: "Vé thường",
        price: 400000,
        stock: 90,
        rating: 4.8,
        emoji: "🎹"
    },
    {
        id: 100008,
        name: "The Grand Music Show",
        type: "Vé VIP",
        price: 1500000,
        stock: 30,
        rating: 5.0,
        emoji: "🏆"
    }
];

// GIỎ HÀNG
let cart = [];

// Đơn hàng đang chờ xác nhận thanh toán
let pendingCheckout = null;

// ============================================
// ĐỊNH DẠNG TIỀN VIỆT NAM
// ============================================

function formatVND(amount) {
    return Number(amount).toLocaleString("vi-VN") + " VNĐ";
}

// ============================================
// TÌM SẢN PHẨM THEO ID
// ============================================

function findProduct(id) {
    return products.find(product => product.id === Number(id));
}

// ============================================
// LƯU VÀ ĐỌC TỒN KHO
// ============================================

function loadStock() {
    try {
        const savedStock = JSON.parse(
            localStorage.getItem("concertStock")
        );

        if (savedStock) {
            products.forEach(product => {
                if (savedStock[product.id] !== undefined) {
                    product.stock = Number(savedStock[product.id]);
                }
            });
        }
    } catch (error) {
        console.error("Không thể đọc tồn kho:", error);
    }
}

function saveStock() {
    const stockData = {};

    products.forEach(product => {
        stockData[product.id] = product.stock;
    });

    localStorage.setItem(
        "concertStock",
        JSON.stringify(stockData)
    );
}

// ============================================
// LƯU VÀ ĐỌC ĐƠN HÀNG
// ============================================

function loadOrders() {
    try {
        return JSON.parse(
            localStorage.getItem("concertOrders")
        ) || [];
    } catch (error) {
        console.error("Không thể đọc đơn hàng:", error);
        return [];
    }
}

function saveOrders(orders) {
    localStorage.setItem(
        "concertOrders",
        JSON.stringify(orders)
    );
}

// ============================================
// HIỂN THỊ DANH SÁCH SẢN PHẨM
// ============================================

function displayProducts(list = products) {
    const container = document.getElementById("product-list");

    if (!container) return;

    if (list.length === 0) {
        container.innerHTML = "<p>Không tìm thấy vé phù hợp.</p>";
        return;
    }

    container.innerHTML = list.map(product => `
        <div class="product-card">
            <div class="product-image">
                ${product.emoji}
            </div>

            <h3>${escapeHTML(product.name)}</h3>

            <p>Loại vé: ${escapeHTML(product.type)}</p>

            <p>Đánh giá: ⭐ ${product.rating}</p>

            <p>Giá: <strong>${formatVND(product.price)}</strong></p>

            <p>Còn lại: ${product.stock} vé</p>

            <button
                onclick="addToCart(${product.id})"
                ${product.stock <= 0 ? "disabled" : ""}
            >
                ${product.stock <= 0 ? "HẾT VÉ" : "THÊM VÀO GIỎ"}
            </button>
        </div>
    `).join("");
}

// ============================================
// TÌM KIẾM VÀ LỌC SẢN PHẨM
// ============================================

function filterProducts() {
    const searchInput = document.getElementById("search-input");
    const priceFilter = document.getElementById("price-filter");

    const keyword = searchInput
        ? searchInput.value.toLowerCase().trim()
        : "";

    const priceValue = priceFilter
        ? priceFilter.value
        : "all";

    let filtered = products.filter(product => {
        return product.name.toLowerCase().includes(keyword) ||
            String(product.id).includes(keyword) ||
            product.type.toLowerCase().includes(keyword);
    });

    if (priceValue === "low") {
        filtered = filtered.filter(product => product.price <= 500000);
    } else if (priceValue === "medium") {
        filtered = filtered.filter(
            product => product.price > 500000 &&
                       product.price <= 1000000
        );
    } else if (priceValue === "high") {
        filtered = filtered.filter(product => product.price > 1000000);
    }

    displayProducts(filtered);
}

// ============================================
// THÊM VÉ VÀO GIỎ HÀNG
// ============================================

function addToCart(id) {
    const product = findProduct(id);

    if (!product || product.stock <= 0) {
        alert("Sản phẩm hiện không còn vé!");
        return;
    }

    const existingItem = cart.find(item => item.id === product.id);

    if (existingItem) {
        if (existingItem.quantity >= product.stock) {
            alert("Số lượng vé vượt quá tồn kho!");
            return;
        }

        existingItem.quantity++;
    } else {
        cart.push({
            id: product.id,
            name: product.name,
            type: product.type,
            price: product.price,
            quantity: 1
        });
    }

    displayCart();
}

// ============================================
// TĂNG SỐ LƯỢNG
// ============================================

function increaseQuantity(id) {
    const item = cart.find(item => item.id === Number(id));
    const product = findProduct(id);

    if (!item || !product) return;

    if (item.quantity >= product.stock) {
        alert("Không đủ vé trong kho!");
        return;
    }

    item.quantity++;
    displayCart();
}

// ============================================
// GIẢM SỐ LƯỢNG
// ============================================

function decreaseQuantity(id) {
    const item = cart.find(item => item.id === Number(id));

    if (!item) return;

    item.quantity--;

    if (item.quantity <= 0) {
        cart = cart.filter(cartItem => cartItem.id !== Number(id));
    }

    displayCart();
}

// ============================================
// XÓA VÉ KHỎI GIỎ HÀNG
// ============================================

function removeFromCart(id) {
    cart = cart.filter(item => item.id !== Number(id));
    displayCart();
}

// ============================================
// TÍNH TỔNG TIỀN
// ============================================

function calculateTotal() {
    return cart.reduce((total, item) => {
        return total + item.price * item.quantity;
    }, 0);
}

// ============================================
// HIỂN THỊ GIỎ HÀNG
// ============================================

function displayCart() {
    const container = document.getElementById("cart-list");
    const totalElement = document.getElementById("cart-total");

    if (!container) return;

    if (cart.length === 0) {
        container.innerHTML = "<p>Giỏ hàng đang trống.</p>";
    } else {
        container.innerHTML = cart.map(item => `
            <div class="cart-item">
                <h4>${escapeHTML(item.name)}</h4>

                <p>${formatVND(item.price)}</p>

                <div class="cart-actions">
                    <button onclick="decreaseQuantity(${item.id})">-</button>

                    <span>${item.quantity}</span>

                    <button onclick="increaseQuantity(${item.id})">+</button>

                    <button onclick="removeFromCart(${item.id})">
                        Xóa
                    </button>
                </div>

                <p>
                    Thành tiền:
                    <strong>
                        ${formatVND(item.price * item.quantity)}
                    </strong>
                </p>
            </div>
        `).join("");
    }

    if (totalElement) {
        totalElement.textContent = formatVND(calculateTotal());
    }
}

// ============================================
// TẠO MÃ ĐƠN HÀNG
// ============================================

function generateOrderId() {
    return "CT" +
        Date.now().toString() +
        Math.floor(Math.random() * 1000);
}

// ============================================
// HIỂN THỊ QR THANH TOÁN MÔ PHỎNG
// ============================================

function showPaymentQR(customerName) {
    if (cart.length === 0) {
        alert("Giỏ hàng đang trống!");
        return;
    }

    // Kiểm tra tồn kho trước khi hiển thị QR
    for (const item of cart) {
        const product = findProduct(item.id);

        if (!product || item.quantity > product.stock) {
            alert("Số lượng vé hiện không đủ. Vui lòng kiểm tra lại!");
            return;
        }
    }

    const orderId = generateOrderId();
    const total = calculateTotal();

    pendingCheckout = {
        id: orderId,
        customerName: customerName,
        items: cart.map(item => ({ ...item })),
        total: total,
        date: new Date().toISOString()
    };

    // Nội dung QR chỉ là dữ liệu mô phỏng
    const qrContent = [
        "MINI_CONCERT_TICKET",
        "DEMO_PAYMENT",
        "ORDER:" + orderId,
        "CUSTOMER:" + customerName,
        "AMOUNT:" + total + " VND",
        "NO_REAL_TRANSACTION"
    ].join("|");

    const qrURL =
        "https://api.qrserver.com/v1/create-qr-code/" +
        "?size=250x250&data=" +
        encodeURIComponent(qrContent);

    let modal = document.getElementById("payment-modal");

    if (!modal) {
        modal = document.createElement("div");
        modal.id = "payment-modal";

        document.body.appendChild(modal);
    }

    modal.innerHTML = `
        <div class="payment-overlay">
            <div class="payment-box">

                <h2>THANH TOÁN ĐƠN HÀNG</h2>

                <p>Khách hàng:
                    <strong>${escapeHTML(customerName)}</strong>
                </p>

                <p>Mã đơn hàng:
                    <strong>${escapeHTML(orderId)}</strong>
                </p>

                <p>Tổng tiền cần thanh toán:</p>

                <h2 class="payment-total">
                    ${formatVND(total)}
                </h2>

                <div class="qr-container">
                    <img
                        src="${qrURL}"
                        alt="Mã QR thanh toán mô phỏng"
                        class="payment-qr"
                    >
                </div>

                <p class="payment-note">
                    Đây là mã QR mô phỏng phục vụ trình diễn đồ án.
                    Không phải mã chuyển khoản ngân hàng.
                </p>

                <p class="payment-status">
                    Trạng thái: Chờ xác nhận thanh toán
                </p>

                <button
                    class="confirm-payment-button"
                    onclick="confirmPayment()"
                >
                    XÁC NHẬN ĐÃ THANH TOÁN
                </button>

                <button
                    class="cancel-payment-button"
                    onclick="cancelPayment()"
                >
                    HỦY THANH TOÁN
                </button>

            </div>
        </div>
    `;

    modal.style.display = "block";
}

// ============================================
// BẮT ĐẦU THANH TOÁN
// ============================================

function checkout() {
    if (cart.length === 0) {
        alert("Bạn chưa có vé trong giỏ hàng!");
        return;
    }

    const customerName = prompt("Vui lòng nhập tên khách hàng:");

    if (customerName === null) {
        return;
    }

    if (customerName.trim() === "") {
        alert("Vui lòng nhập tên khách hàng!");
        return;
    }

    showPaymentQR(customerName.trim());
}

// ============================================
// XÁC NHẬN THANH TOÁN MÔ PHỎNG
// ============================================

function confirmPayment() {
    if (!pendingCheckout) {
        alert("Không tìm thấy thông tin thanh toán!");
        return;
    }

    // Kiểm tra tồn kho lần nữa
    for (const item of pendingCheckout.items) {
        const product = findProduct(item.id);

        if (!product || item.quantity > product.stock) {
            alert("Không đủ vé để hoàn tất đơn hàng!");

            pendingCheckout = null;
            closePaymentModal();
            return;
        }
    }

    const order = {
        id: pendingCheckout.id,
        customerName: pendingCheckout.customerName,
        date: pendingCheckout.date,
        items: pendingCheckout.items,
        total: pendingCheckout.total,
        status: "Đã xác nhận thanh toán mô phỏng"
    };

    const orders = loadOrders();

    // Lưu đơn hàng và trừ tồn kho
    const oldStock = products.map(product => ({
        id: product.id,
        stock: product.stock
    }));

    try {
        orders.push(order);

        // Trừ số lượng vé
        pendingCheckout.items.forEach(item => {
            const product = findProduct(item.id);
            product.stock -= item.quantity;
        });

        saveOrders(orders);
        saveStock();

    } catch (error) {
        // Khôi phục tồn kho nếu có lỗi
        oldStock.forEach(saved => {
            const product = findProduct(saved.id);

            if (product) {
                product.stock = saved.stock;
            }
        });

        try {
            saveStock();
        } catch (e) {
            console.error(e);
        }

        alert("Có lỗi khi lưu đơn hàng. Vui lòng thử lại!");
        console.error(error);
        return;
    }

    cart = [];
    pendingCheckout = null;

    closePaymentModal();

    displayCart();
    displayProducts();
    displayOrders();

    alert("Thanh toán mô phỏng thành công! Đơn hàng đã được tạo.");

    const orderDetail = document.getElementById("order-detail");

    if (orderDetail) {
        showOrderDetail(order.id);
        orderDetail.scrollIntoView({
            behavior: "smooth",
            block: "start"
        });
    }
}

// ============================================
// HỦY THANH TOÁN
// ============================================

function cancelPayment() {
    const confirmed = confirm(
        "Bạn có chắc muốn hủy thanh toán không?"
    );

    if (!confirmed) return;

    pendingCheckout = null;
    closePaymentModal();
}

// ============================================
// ĐÓNG CỬA SỔ THANH TOÁN
// ============================================

function closePaymentModal() {
    const modal = document.getElementById("payment-modal");

    if (modal) {
        modal.style.display = "none";
        modal.innerHTML = "";
    }
}

// ============================================
// HIỂN THỊ DANH SÁCH ĐƠN HÀNG
// ============================================

function displayOrders() {
    const container = document.getElementById("order-list");

    if (!container) return;

    const orders = loadOrders();

    if (orders.length === 0) {
        container.innerHTML = "<p>Bạn chưa có đơn hàng nào.</p>";
        return;
    }

    container.innerHTML = orders.map(order => `
        <div class="order-card">

            <h3>Đơn hàng: ${escapeHTML(order.id)}</h3>

            <p>Khách hàng:
                ${escapeHTML(order.customerName || "Khách hàng")}
            </p>

            <p>Ngày đặt:
                ${formatDate(order.date)}
            </p>

            <p>Tổng tiền:
                <strong>${formatVND(order.total)}</strong>
            </p>

            <p>Trạng thái:
                ${escapeHTML(order.status || "Đã xác nhận")}
            </p>

            <div class="order-actions">

                <button
                    onclick="showOrderDetail('${escapeHTML(order.id)}')"
                >
                    XEM CHI TIẾT
                </button>

                <button
                    class="delete-order-button"
                    onclick="deleteOrder('${escapeHTML(order.id)}')"
                >
                    XÓA ĐƠN
                </button>

            </div>
        </div>
    `).join("");
}

// ============================================
// XEM CHI TIẾT ĐƠN HÀNG
// ============================================

function showOrderDetail(orderId) {
    const container = document.getElementById("order-detail");

    if (!container) return;

    const orders = loadOrders();

    const order = orders.find(
        item => String(item.id) === String(orderId)
    );

    if (!order) {
        container.innerHTML = "<p>Không tìm thấy đơn hàng.</p>";
        return;
    }

    const itemsHTML = (order.items || []).map(item => `
        <div class="order-detail-item">
            <p>${escapeHTML(item.name || item.productName || "Vé ca nhạc")}</p>
            <p>Loại vé: ${escapeHTML(item.type || "Không xác định")}</p>
            <p>Số lượng: ${item.quantity}</p>
            <p>Đơn giá: ${formatVND(item.price)}</p>
            <p>Thành tiền:
                ${formatVND(item.price * item.quantity)}
            </p>
        </div>
    `).join("");

    container.innerHTML = `
        <div class="order-detail-card">

            <h2>CHI TIẾT ĐƠN HÀNG</h2>

            <p>Mã đơn: ${escapeHTML(order.id)}</p>

            <p>Khách hàng:
                ${escapeHTML(order.customerName || "Khách hàng")}
            </p>

            <p>Ngày đặt: ${formatDate(order.date)}</p>

            <hr>

            ${itemsHTML}

            <hr>

            <h3>Tổng thanh toán:
                ${formatVND(order.total)}
            </h3>

            <p>Trạng thái:
                ${escapeHTML(order.status || "Đã xác nhận")}
            </p>

        </div>
    `;
}

// ============================================
// XÓA ĐƠN HÀNG VÀ HOÀN LẠI TỒN KHO
// ============================================

function deleteOrder(orderId) {
    const orders = loadOrders();

    const orderIndex = orders.findIndex(
        order => String(order.id) === String(orderId)
    );

    if (orderIndex === -1) {
        alert("Không tìm thấy đơn hàng!");
        return;
    }

    const confirmed = confirm(
        "Bạn có chắc muốn xóa đơn hàng này không? " +
        "Số lượng vé sẽ được hoàn lại kho."
    );

    if (!confirmed) return;

    const order = orders[orderIndex];

    // Lưu tồn kho cũ để có thể khôi phục khi lưu lỗi
    const oldStock = products.map(product => ({
        id: product.id,
        stock: product.stock
    }));

    try {
        // Hoàn lại vé
        (order.items || []).forEach(item => {
            const product = findProduct(item.id);

            if (product) {
                product.stock += Number(item.quantity);
            }
        });

        // Xóa đơn hàng
        orders.splice(orderIndex, 1);

        saveOrders(orders);
        saveStock();

    } catch (error) {
        // Khôi phục tồn kho nếu xảy ra lỗi
        oldStock.forEach(saved => {
            const product = findProduct(saved.id);

            if (product) {
                product.stock = saved.stock;
            }
        });

        alert("Không thể xóa đơn hàng. Vui lòng thử lại!");
        console.error(error);
        return;
    }

    displayOrders();
    displayProducts();

    const detail = document.getElementById("order-detail");

    if (detail) {
        detail.innerHTML = "";
    }

    alert("Đã xóa đơn hàng và hoàn lại số lượng vé!");
}

// ============================================
// ĐỊNH DẠNG NGÀY THÁNG
// ============================================

function formatDate(dateString) {
    if (!dateString) return "Không xác định";

    const date = new Date(dateString);

    if (Number.isNaN(date.getTime())) {
        return "Không xác định";
    }

    return date.toLocaleString("vi-VN");
}

// ============================================
// CHỐNG CHÈN HTML KHÔNG AN TOÀN
// ============================================

function escapeHTML(value) {
    return String(value ?? "").replace(/[&<>"']/g, character => {
        const entities = {
            "&": "&amp;",
            "<": "&lt;",
            ">": "&gt;",
            '"': "&quot;",
            "'": "&#39;"
        };

        return entities[character];
    });
}

// ============================================
// KHỞI TẠO WEBSITE
// ============================================

document.addEventListener("DOMContentLoaded", function () {

    loadStock();

    displayProducts();
    displayCart();
    displayOrders();

    const searchInput = document.getElementById("search-input");

    if (searchInput) {
        searchInput.addEventListener("input", filterProducts);
    }

    const priceFilter = document.getElementById("price-filter");

    if (priceFilter) {
        priceFilter.addEventListener("change", filterProducts);
    }

    const checkoutButton = document.getElementById("checkout-button");

    if (checkoutButton) {
        checkoutButton.addEventListener("click", checkout);
    }

});
