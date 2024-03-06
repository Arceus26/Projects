<?php include('server.php') ?>
<!DOCTYPE html>
<html>
<head>
  <title>Sign up</title>
  <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" />
  <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" />
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
<link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" />
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
        <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" />
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
        <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" />

		<link rel="stylesheet" href="sty.css">
</head>
<body>

<section id="header">  <a href="#">   <img src="scr2.jpg"  class="logo"  alt=""></a>     
        
		<div>
			<ul id = "navbar">
				<li> <a href ="Indx.php">Home</a></li>
				<li> <a href ="Reviws.php">Reviews</a></li>
				<li> <a href ="cart.html">Checkout</a></li>
				<li> <a class="active" href ="Sign.php">Sign in</a></li>
				<a href="#" id="close"><i class="far fa-times"></i></a>
			</ul>
		</div>
		<div id="mobile">
            <i id="bar" class="fas fa-outdent"></i>
        </div>
	</section>



  <div class="header">
  	<h8>Sign up</h8>
  </div>
	

  <form method="post" action="register.php">
  	<?php include('errors.php'); ?>

  	<div class="input-group">
  	  <label>Username:</label>
  	  <input type="text" name="username" value="<?php echo $username; ?>">
  	</div>

  	<div class="input-group">
  	  <label>Email:</label>
  	  <input type="email" name="email" value="<?php echo $email; ?>">
  	</div>

  	<div class="input-group">
  	  <label>Password:</label>
  	  <input type="password" name="password_1">
	</div>
	
	<div class="input-group">
  	  <label>Confirm password:</label>
  	  <input type="password" name="password_2">
  	</div>
	
	<div class="containerS">
  	<div class="input-group">
  	  <button type="submit" class="btn" name="reg_user">Sign up</button>
  	</div>

</div>


  	<p>
  		Already have an account? <a href="Sign.php">Sign in</a>
  	</p>
  </form>


  <style>
.containerS {
  text-align: center;
  padding: 10px;
}
</style>



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
		<script src="script.js"></script>
</body>
</html>