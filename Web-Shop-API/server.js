const sqlite = require("sqlite3").verbose();
let db = my_database("./products.db");

var express = require("express");
var app = express();

var path = require("path");
var bodyParser = require("body-parser");

var cors = require(`cors`);
app.use(cors());

app.use(bodyParser.json());

app.get("/product", function (req, res) {
  db.all(`SELECT * FROM products`, function (err, rows) {
    if (err) {
      error = new Error("Error fetching all products");
      res.status(500).json({
        message: error,
      });
      return;
    } else {
      res.status(200).json({
        message: "Products were fetched",
        rows: rows,
      });
      return;
    }
  });
});

app.get("/product/:id", function (req, res) {
  db.all(
    `SELECT * FROM products WHERE id=?`,
    [req.params.id],
    function (err, rows) {
      if (err) {
        error = new Error(`Error fetching product with id ${req.params.id}`);
        console.log(err);
        res.status(500).json({
          message: error,
        });
        return;
      } else {
        res.status(200).json({
          message: "Product was fetched",
          rows: rows,
        });
        return;
      }
    }
  );
});

app.post("/product/create", function (req, res) {
  let product = req.body;

  if (
    product.product == null ||
    product.origin == null ||
    product.best_before_date == null ||
    product.amount == null
  ) {
    res.status(400).json({
      message: `Failed constraints`,
    });
    return;
  } else {
    db.run(
      `INSERT INTO products (product, origin, best_before_date, amount, image) VALUES (?, ?, ?, ?, ?)`,
      [
        product.product,
        product.origin,
        product.best_before_date,
        product.amount,
        product.image,
      ]
    );
    db.all(`select count(*) as count from products`, function (err, result) {
      if (!err) {
        res.status(201).json({
          message: "Product was created",
          productID: result[0].count,
        });
        return;
      }
    });
  }
});

app.delete("/product/delete", function (req, res) {
  db.run(`DELETE FROM products WHERE id`, function (err, result) {
    res.status(204).json({
      message: "All products were deleted",
    });
    return;
  });
});

app.delete("/product/delete/:id", function (req, res) {
  db.run(
    `DELETE FROM products WHERE id=${req.params.id}`,
    function (err, result) {
      res.status(204).json({
        message: `Product with id: ${req.params.id} was deleted`,
      });
      return;
    }
  );
});

app.put("/product/update/:id", function (req, res) {
  let product = res.json(req.body);

  if (
    product.product == null ||
    product.origin == null ||
    product.best_before_date == null ||
    product.amount == null
  ) {
    res.status(400).json({
      message: `Failed constraints`,
    });
  } else {
    db.run(
      `UPDATE products SET product = ${product.product}, origin = ${product.origin}, best_before_date = ${product.best_before_date},
    amount = ${product.amount}, image = ${product.image}  WHERE id=${req.params.id}`,
      function (err, result) {
        if (!err) {
          res.status(201).json({
            message: `Product with id: ${req.params.id} was updated`,
            productID: req.body,
          });
        }
      }
    );
  }
  next(res);
});

app.get("/help", function (req, res) {
  res.sendFile(path.join(__dirname + "/help.html"));
});

app.listen(3000);
console.log(
  "Your Web server should be up and running, waiting for requests to come in. Try http://localhost:3000/help"
);

function my_database(filename) {
  var db = new sqlite.Database(filename, (err) => {
    if (err) {
      console.error(err.message);
    }
  });
  db.serialize(() => {
    db.run(`
        	CREATE TABLE IF NOT EXISTS products
        	(id 	  INTEGER PRIMARY KEY,
        	product	CHAR(100) NOT NULL,
        	origin 	CHAR(100) NOT NULL,
        	best_before_date 	CHAR(20) NOT NULL,
          amount  CHAR(20) NOT NULL,
        	image   CHAR(254) NOT NULL
        	)`);
    db.all(`select count(*) as count from products`, function (err, result) {
      if (result[0].count == 0) {
        db.run(
          `INSERT INTO products (product, origin, best_before_date, amount, image) VALUES (?, ?, ?, ?, ?)`,
          [
            "Apples",
            "The Netherlands",
            "November 2019",
            "100kg",
            "https://upload.wikimedia.org/wikipedia/commons/thumb/e/ee/Apples.jpg/512px-Apples.jpg",
          ]
        );
        console.log("Inserted dummy Apples entry into empty product database");
      } else {
        console.log(
          "Database already contains",
          result[0].count,
          " item(s) at startup."
        );
      }
    });
  });
  return db;
}
