<?php
session_start();
$ouraddress = "";

$session = $_SESSION['usertoken'];
if(empty($session)) {
   header("Location: login.php");
   die();
}
require_once 'api/RPC/includes/jsonRPCClient.php'; 
$bitcoin = new jsonRPCClient('http://root:passhere@127.0.0.1:8332/');

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
