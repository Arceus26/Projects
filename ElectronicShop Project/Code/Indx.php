<?php

require_once 'connection.php';

$sql = "SELECT * FROM product1";
$all_product = $conn->query($sql);

?>




<!DOCTYPE html>
<html lang="en">

    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Electronics shop</title>
        <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" />

        <link rel="stylesheet" href="sty.css">
    </head>  

    <body>

        <section id="header">  <a href="#">   <img src="scr2.jpg"  class="logo"  alt=""></a>     
        
            <div>
                <ul id = "navbar">
                    <li> <a class="active" href ="Indx.html">Home</a></li>
                    <li> <a href ="Reviws.php">Reviews</a></li>
                    <li> <a href ="cart.html">Checkout <i class="far fa-shopping-bag"></i></a></li>
                    <li> <a href ="Sign.php">Sign in</a></li>
                    <a href="#" id="close"><i class="far fa-times"></i></a>
                </ul>
            </div>
            <div id="mobile">
                <a href="cart.html"><i class="far fa-shopping-bag"></i></a>
                <i id="bar" class="fas fa-outdent"></i>
            </div>
        </section>

        <section id="hero">
            <h2> Electronics Shop </h2>
            <h1> New products </h1>
            <h7> Welcome Back </h7>        
            <h4> SHOP NOW! </h4>
        </section>


        <section id="product1" class="section-p1"> 
            <h4>The best offers!</h4>
            <h3> Top products </h3>
            <h3> Just here </h3>


            <div class="pro-container">
            <?php

                while($row = mysqli_fetch_assoc($all_product)) {

            ?>

                <div class="pro">
                    <img src="<?php echo $row["product_image"];  ?>" alt="">
                        <div class="des">
                        <span> ID:<?php echo $row["ID"]; ?> </span>
                        <h5> <?php  echo $row["product_name"]; ?> </h5>
                            <div class="star">
                            <i class = "fas fa-star"></i>
                            <i class = "fas fa-star"></i>                                    
                            <i class = "fas fa-star"></i>
                            <i class = "fas fa-star"></i>
                            <i class = "fas fa-star"></i>
                        </div>
                        <h4> $<?php echo $row["price"]; ?> </h4>
                    </div>

                    <button class="addB"
                    data-id="<?php echo $row["ID"]; ?>"
                    data-title="<?php echo $row["product_name"]; ?>"
                    data-image=" <?php echo $row["product_image"]; ?>"
                    data-price=" <?php echo $row["price"]; ?> ">
                    Add to Cart</button>
                </div> 


            <?php
                    }
                ?>
        </section>
        

        <div class="divider"></div> 



        <footer class="section-p1">
            <div class="col">
                <img class="logo" src="scr2.jpg" alt="">
                <h3>Contact</h3>
                <p><strong>Adress: </strong>Aleea Studentilor</p>
                <p><strong>Phone: </strong> 07864547</p>
                <p><strong>Hours: </strong>8:00 - 18:00, Mon - Sat</p>
                <div class="follow">
                    <h3>Folow us</h3>
                    <div class="icon">
                        <i class="fab fa-facebook-f"></i>
                        <i class="fab fa-twitter"></i>
                        <i class="fab fa-instagram"></i>
                        <i class="fab fa-pinterest-p"></i>
                        <i class="fab fa-youtube"></i>
                    </div>
                </div>
            </div>

            <div class="col">
                <h3>About</h3><br>
                <a href="#">About us</a>
                <a href="#">Delivery Information</a>
                <a href="#">Privacy Policy</a>
                <a href="#">Terms & Conditions</a>
                <a href="#">Contact us</a>
            </div>

            <div class="col">
                <h3>My account</h3><br>
                <a href="#">Sing in</a>
                <a href="#">View Cart</a>
                <a href="#">My Whishlist</a>
                <a href="#">Track My Order</a>
                <a href="#">Help</a>
            </div>

            <div class="col install">
                <h3>Install App</h3>
                <p>From App Store or Google Play</p>
                <div class="row">
                    <img src="app.jpg" alt="">
                    <img src="play.jpg" alt="">
                </div>
                <p>Secured Payment Gateways</p>
                <img src="pay.png" alt="">
            </div> 

            <div class="copyright">
                <p>© 2023, Electronics Shop - Html Css Website</p>
            </div>
        </footer>



        <script src="script.js"></script>
        <script>
            document.addEventListener('DOMContentLoaded', () => {
                const bar = document.getElementById('bar');
                const nav = document.getElementById('navbar');
                const close = document.getElementById("close");
    
                if (bar) {
                    bar.addEventListener('click', () => {
                        nav.classList.add('active');
                    });
                }

                if (close) {
                    close.addEventListener('click', () => {
                        nav.classList.remove('active');
                    });
                }

            });
        </script>
    </body>
</html>