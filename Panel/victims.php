<?php

session_start();
$session = $_SESSION['victim'];
if(empty($session)) {
   header("Location: login.php");
   die();
}
    $dsn = 'mysql:host=localhost;dbname=db'; // define host name and database name
    $username = 'root'; // define the username
    $pwd='passhere'; // password
    try {
        $db = new PDO($dsn, $username, $pwd);
    }
    catch (PDOException $e) {
        $error_message = $e->getMessage();
        echo "error";
        
	}





?>
