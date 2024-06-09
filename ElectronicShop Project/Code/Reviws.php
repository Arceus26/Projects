<?php include('conectR.php') ?>

<?php

$db = mysqli_connect('localhost', 'root', '', 'pi');

$sql = "SELECT * FROM reviews";
$result = mysqli_query($db, $sql);

if (!$result) {
    die("Eroare la interogare: " . mysqli_error($db));
}

?>

<!DOCTYPE html>
<html lang="en">

    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Reviews</title>
        <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" />
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
        <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" />

        <link rel="stylesheet" href="sty.css">
    
    </head>  

    <body>

        <section id="head_rw">  <a href="#">   <img src="scr2.jpg"  class="logo"  alt=""></a>     
        
            <div>
                <ul id = "navbar">
                    <li> <a href ="Indx.php">Home</a></li>
                    <li> <a class="active" href ="Reviws.php">Reviews</a></li>
                    <li> <a href ="cart.html">Checkout</a></li>
                    <li> <a href ="Sign.php">Sign in</a></li>
                    <a href="#" id="close"><i class="far fa-times"></i></a>
                </ul>
            </div>
            <div id="mobile">
                <i id="bar" class="fas fa-outdent"></i>
            </div>
        </section>


          
          <div class="rev-section">
          
          <h4 class="title">Reviews section</h4>
          <p class="note">Here are the reviews of our clients</p>
          

          <div class="reviews">
          
          

<?php

while ($row = mysqli_fetch_assoc($result)) {
    $productId = $row["ID"];

    $productQuery = "SELECT * FROM product1 WHERE ID = '$productId'";
    $productResult = mysqli_query($db, $productQuery);
    $product = mysqli_fetch_assoc($productResult);

    if ($product) {
        echo '<div class="review">';
        echo '<div class="head-review">';
        echo '<img src="' . $product["product_image"] . '" class="imggg" width="250px">';
        echo '</div>';
        echo '<div class="body-review">';
        echo '<div class="name-review">' . $row["name"] . '</div>';
        echo '<div class="place-review">' . $row["city"] . '</div>';
        echo '<div class="rating">
         <i class="fas fa-star"></i>
         <i class="fas fa-star"></i>
         <i class="fas fa-star"></i>
         <i class="fas fa-star"></i>
         <i class="fas fa-star-half"></i> </div>';
         

        
        echo '<div class="desc-review">' . $row["review"] . '</div>';

        echo '</div>';
         echo '</div>';
    }
}


?>
   
</div>       
</div>
          

<div class="divider"></div> 


<section id="product1" class="section-p1"> 
          <h4> Write an review here! </h4>
</section>


          <section>

          <form method="post" action="Reviws.php" id="reviewForm">
  	      <?php include('errors.php'); ?>

  

          <div class="input-review">
            <label>Enter your name:</label>
            <input type="text" name="name" value="<?php  echo $name; ?>">
        </div>

        <div class="input-review">
            <label>Enter your city:</label>
            <input type="text" name="city" value="<?php echo $city; ?>">
        </div>

        <div class="input-review">
            <label>Your ID product:</label>
            <input type="text" name="ID" value="<?php echo $ID; ?>">
        </div>

        <div class="input-review">
            <label>Personal reviw:</label>
            <input type="text" name="review" value="<?php echo $review; ?>">
        </div>

        <div class="containerR">
            <button type="submit" class="btnR" name="reg_R">Submit</button>
          </div>

        </form>

    </section>
    


        <style>

form {
    max-width: 1000px; 
    margin: 0 auto;
    padding: 30px;
}

#reviewForm {
    max-width: 1500px; 
    margin: 0 auto;
  }


.containerR {
  text-align: center;
  padding: 20px;
}

.btnR {
padding: 15px;
  font-size: 18px;
  color: white;
  background: #317b60;
  border: none;
  border-radius: 8px;
  display: inline-block;
}


.input-review {
    margin-bottom: 15px;
    align-items: center;
}

label {
display: inline-block;
  margin-bottom: 11px;
  padding: 7px;
  width: 360px;
  font-weight: bolder; 
  color: #333;
  
}


input {
padding: 13px;
flex: 2;
box-sizing: border-box;
width: 100%;
}

@media (max-width: 678px) {
    label {
        width: 100%;
    }
}

/* Stiluri pentru telefoane */
@media (max-width: 477px) {
    label {
        width: 100%;
    }
    input {
        width: 100%;
    }
}

@media only screen and (max-width: 800px) {
    label {
        width: 100%;
    }
    input {
        width: 100%;
    }
}


</style>
        


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