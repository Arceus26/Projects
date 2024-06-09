<?php
session_start();

$name = "";
$city = "";
$ID = "";
$review = "";

$errors = array(); 

$db = mysqli_connect('localhost', 'root', '', 'pi');



if (isset($_POST['reg_R'])) {

  $name = mysqli_real_escape_string($db, $_POST['name']);
  $city = mysqli_real_escape_string($db, $_POST['city']);
  $ID = mysqli_real_escape_string($db, $_POST['ID']);
  $review = mysqli_real_escape_string($db, $_POST['review']);
  

  if (!is_numeric($ID)) {
    array_push($errors, "ID must be a numeric value");
  } else {
    $ID = intval($ID);
    if ($ID != $ID) {
      array_push($errors, "ID must be an integer value");
    }
  }
  
  if (empty($name)) { array_push($errors, "Name is required"); }
  if (empty($city)) { array_push($errors, "City is required"); }
  if (empty($ID)) { array_push($errors, "ID is required"); }
  if (empty($review)) {array_push($errors, "Review is required"); }

  
  if (count($errors) == 0) {
 
  	$query = "INSERT INTO reviews (name, city, ID, review) 
  			  VALUES('$name', '$city', '$ID', '$review')";
  	mysqli_query($db, $query);
   
    $name = "";
    $city = "";
    $ID = "";
    $review = "";
  }
}


?>