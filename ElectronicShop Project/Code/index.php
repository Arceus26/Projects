<?php 
  session_start(); 

  if (!isset($_SESSION['username'])) {
  	$_SESSION['msg'] = "You must log in first";
  	header('location: Sign.php');
  }
  if (isset($_GET['logout'])) {
  	session_destroy();
  	unset($_SESSION['username']);
  	header("location: Sign.php");
  }
?>
<!DOCTYPE html>
<html>
<head>
	<title>Home</title>
	<link rel="stylesheet" type="text/css" href="sty.css">
</head>
<body>

<section id="header">  <a href="#">   <img src="scr2.jpg"  class="logo"  alt=""></a>     
        
		<div>
			<ul id = "navbar">
				<li> <a href ="Indx.php">Home</a></li>
				<li> <a href ="Reviws.php">Reviews</a></li>
				<li> <a href ="cart.html">Checkout</a></li>
				<li> <a class="active" href ="Sign.php">Sign in</a></li>

			</ul>
		</div>
	</section>


<div class="header">
	<h8>Home Page</h8>
</div>
<div class="content">
  	
  	<?php if (isset($_SESSION['success'])) : ?>
      <div class="error success" >
      	<h3>
          <?php 
          	echo $_SESSION['success']; 
          	unset($_SESSION['success']);
          ?>
      	</h3>
      </div>
  	<?php endif ?>

    <?php  if (isset($_SESSION['username'])) : ?>
    	<p>Welcome <strong><?php echo $_SESSION['username']; ?></strong></p><br>
    	<p> <a href="index.php?logout='1'" style="color: red;">Log out</a> </p>
    <?php endif ?>
</div>

</body>
</html>