document.addEventListener("DOMContentLoaded", function (event) {
    getData();

    const form = document.getElementById("productForm");
    form.addEventListener("click", function (event) {
        if (event.target.className === 'submit'){
            event.preventDefault();
            submitProduct(form);
        } else if (event.target.className === 'deleteBtn') {
            deleteRowById(event.target.parentNode.parentNode.children[0].innerText)
        }
        
    })
});

// API requests

function resetData() {
    var http = new XMLHttpRequest();
    http.open("DELETE", "http://localhost:3000/product/delete", true);
    http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    http.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 204) {
            var response = this.responseText;
            resetTable();
            getData();
        }
    };
    http.send();
}

function submitProduct(form) {

    var url = "http://localhost:3000/product/create";

    var http = new XMLHttpRequest();
    http.open("POST", url);

    http.setRequestHeader("Accept", "application/json");
    http.setRequestHeader("Content-Type", "application/json");

    http.onreadystatechange = function () {
    if (http.readyState === 4) {
        getDataById(JSON.parse(http.responseText).productID);
    }};

    var data = {
        product: document.getElementById("product").value,
        origin: document.getElementById("origin").value,
        best_before_date: document.getElementById("best_before_date").value,
        amount: document.getElementById("amount").value,
        image: document.getElementById("image").value
    };

    form.reset();

    http.send(JSON.stringify(data));
}

function getData() {
    var http = new XMLHttpRequest();
    http.open("GET", "http://localhost:3000/product", true);
    http.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            var response = this.responseText;
            response = JSON.parse(response);
            if (response.rows != null) {
                loadDataDOM(response.rows);
            }
        }
    };
    http.send();
}

function getDataById(id) {
    var http = new XMLHttpRequest();
    http.open("GET", `http://localhost:3000/product/${id}`, true);
    http.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            var response = this.responseText;
            response = JSON.parse(response);
            if (response.rows != null) {
                loadDataDOM(response.rows);
            }
        }
    };
    http.send();
}

function deleteRowById(id) {
    var http = new XMLHttpRequest();
    http.open("DELETE", `http://localhost:3000/product/delete/${id}`, true);
    http.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 204) {
            var response = this.responseText;
            resetTable();
            getData();
        }
    };
    http.send();
}

// DOM manipulation

function loadDataDOM(products) {
    const productTable = document.querySelector('#t02');
    for (i = 0; i < products.length; i++) {
        if (products[i] != null) {
            let productRow = document.createElement('tr');
            let idCell = document.createElement('td');
            idCell.innerHTML = products[i].id;
            let productCell = document.createElement('td');
            productCell.innerHTML = products[i].product;
            let originCell = document.createElement('td');
            originCell.innerHTML = products[i].origin;
            let bestBeforeCell = document.createElement('td');
            bestBeforeCell.innerHTML = products[i].best_before_date;
            let amountCell = document.createElement('td');
            amountCell.innerHTML = products[i].amount;
            let imageCell = document.createElement('td');
            let image = document.createElement('img');
            image.alt = products[i].product;
            image.src = products[i].image;
            imageCell.appendChild(image);
            let actionCell = document.createElement('td');
            let deleteBtn = document.createElement('button');
            deleteBtn.className = "deleteBtn";
            deleteBtn.innerText = "Delete";
            actionCell.appendChild(deleteBtn);

            productRow.append(idCell, productCell, originCell, bestBeforeCell, amountCell, imageCell, actionCell);
            productTable.append(productRow);
        }
    }
}

function resetTable() {
    const productTable = document.querySelector('#t02');
    const rowsCount = productTable.rows.length;
    for (i = 2; i < rowsCount; i++) {
        productTable.deleteRow(2);
    }
}

function sortTable(n, tableId) {
    var table, rows, switching, i, x, y, shouldSwitch, direction, switchcount = 0;
    table = document.getElementById(tableId);
    switching = true;

    direction = "asc";

    while (switching) {
        i = tableId === "t02" ? 2 : 1;
        switching = false;
        rows = table.rows;

        for (i; i < (rows.length - 1); i++) {
            shouldSwitch = false;
            x = rows[i].getElementsByTagName("TD")[n];
            y = rows[i + 1].getElementsByTagName("TD")[n];

            if (direction == "asc") {
                if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
                    shouldSwitch = true;
                    break;
                }
            } else if (direction == "desc") {
                if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) {
                    shouldSwitch = true;
                    break;
                }
            }
        }

        if (shouldSwitch) {

            rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
            switching = true;

            switchcount++;
        } else {
            if (switchcount == 0 && direction == "asc") {
                direction = "desc";
                switching = true;
            }
        }
    }
}
