import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

""" at a glance helper functions """
#return total shares by symbol
def total_shares(symbol):
    to_return = 0
    stocks = db.execute("SELECT * FROM transactions WHERE symbol=? AND id=?", symbol, session['user_id'])
    for stock in stocks:
        if stock.get("type") == "buy":
            to_return += int(stock.get("volume"))
        elif stock.get("type") == "sell":
            to_return -= int(stock.get("volume"))
    return to_return

#return holding value of a stock
def holding_value(symbol):
    price = lookup(symbol).get("price")
    shares = total_shares(symbol)
    total = price * shares

    return total

#return net worth
def net_value():
    to_return = 0
    stocks = db.execute("SELECT DISTINCT symbol FROM transactions WHERE id=?", session['user_id'])

    def temp_holding_value(symbol):
        price = lookup(symbol).get("price")
        shares= total_shares(symbol)
        return price*shares

    for stock in stocks:
        to_return += temp_holding_value(stock.get("symbol"))

    cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]["cash"]
    return usd(to_return + cash)

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT DISTINCT symbol FROM transactions WHERE id=?", session['user_id'])
    cash = usd(db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]["cash"])
    return render_template("index.html", stocks=stocks, lookup=lookup, usd=usd, cash=cash,
                                        total_shares=total_shares, holding_value=holding_value,
                                        net_value=net_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            amount = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)
        if lookup(symbol) is None:
            return apology("that stock doesn't exist")
            return redirect("/buy")
        price = lookup(symbol).get("price")
        total_value = int(amount) * price
        cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]["cash"]

        if cash < total_value:
            return apology("not enough funds:(((")
        elif int(amount) < 1:
            return apology("invalid amount")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id=?", cash - total_value, session['user_id'])
            db.execute("INSERT INTO transactions (id, symbol, volume, price, type) VALUES(?, ?, ?, ?, ?)",
                        session['user_id'], symbol, int(amount), price, "buy")
            return redirect("/")
    else:
        cash = usd(db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]["cash"])
        return render_template("buy.html", cash=cash)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM transactions WHERE id=?", session['user_id'])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if lookup(request.form.get("symbol")) is None:
            return apology("stock does not exist")
            return redirect("/quote")
        symbol = request.form.get("symbol").upper()
        price = usd(lookup(symbol).get("price"))
        name = lookup(symbol).get("name")

        return render_template("return_quote.html", symbol=symbol, price=price, name=name)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        #error checking
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        user_check = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        #check if username in use
        if len(user_check) == 1:
            return apology("username already in use")
        else:
            username = request.form.get("username")
            pw = generate_password_hash(request.form.get("password"))
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, pw)
            return redirect("/")
    else:
        return render_template("register.html")

@app.route("/reset_pass", methods=["GET", "POST"])
@login_required
def reset_pass():
    """Reset user password"""

    if request.method=="POST":
        #error checking
        if not request.form.get("old_password"):
            return apology("incorrect password", 400)
        elif not request.form.get("new_password"):
            return apology("must provide password", 400)
        elif request.form.get("new_password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        pass_check = db.execute("SELECT * FROM users WHERE id =?", session['user_id'])
        if not check_password_hash(pass_check[0]["hash"], request.form.get("old_password")):
            return apology("password already in use", 400)
        #check if password is in use
        elif request.form.get("old_password") == request.form.get("new_password"):
            return apology("new password must be different", 400)
        else:
            db.execute("UPDATE users SET hash = ? WHERE id=?", generate_password_hash(request.form.get("new_password")), session['user_id'])
            return redirect("/")
    else:
        return render_template("reset_pass.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").lower()
        try:
            amount = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)
        price = lookup(symbol).get("price")
        total_value = int(amount) * price
        cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]["cash"]

        stocks = db.execute("SELECT * FROM transactions WHERE symbol=? AND id=?", symbol, session['user_id'])
        if len(stocks) == 0:
            return apology("you do not own any of this stock!", 400)
        elif total_shares(symbol) < int(amount):
            return apology("you do not own enough of this stock to sell", 400)
        elif int(amount) < 0:
            return apology("invalid amount", 400)
        else:
            db.execute("UPDATE users SET cash = ? WHERE id=?", cash + total_value, session['user_id'])
            db.execute("INSERT INTO transactions (id, symbol, volume, price, type) VALUES(?, ?, ?, ?, ?)",
                        session['user_id'], symbol, int(amount), price, "sell")
        return redirect("/")
    else:
        stocks = db.execute("SELECT DISTINCT symbol FROM transactions WHERE id=?", session['user_id'])
        return render_template("sell.html", stocks=stocks, total_shares=total_shares)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
