<?php
include_once("config.php");


if (!empty($session)) 
{   
    session_destroy();   
    session_unset(); 
    header("Location:login.php");    
} 
else{
	
    header("Location:login.php");
}
?>