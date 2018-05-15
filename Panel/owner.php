<?php

session_start();

    $dsn = 'mysql:host=localhost;dbname=db'; // define host name and database name
    $username = 'root'; // define the username
    $pwd='e60603519ea0D$'; // password
    try {
        $db = new PDO($dsn, $username, $pwd);
    }
    catch (PDOException $e) {
        $error_message = $e->getMessage();
        echo "error";
        
    }
if(!empty($_POST['username']) && !empty($_POST['password'])){
$usernamez = $_POST['username'];

$username = hash('sha256', $usernamez);
$password = $_POST['password'];
$passwordhash = hash('sha256', $password);
if(!empty($username) && !empty($password)){
$statement = "SELECT `id` FROM `users` WHERE username = :username AND password = :password";
if($sth = $db->prepare($statement)){
    $sth->bindParam(':username', $username);
    $sth->bindParam(':password', $passwordhash);
    $sth->execute();
    if($sth->rowCount() > 0){
        $_SESSION['usertoken'] = $username;
        header("Location: index.php");
        die();
    }

}

}

}

?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">
        <meta name="description" content="">
        <meta name="keyword" content="">

        <title>Ladon Ransomware</title>

        <!-- Theme icon -->

        <!-- Theme Css -->
        <link href="assets/css/bootstrap.min.css" rel="stylesheet">
        <link href="assets/css/slidebars.min.css" rel="stylesheet">
        <link href="assets/css/icons.css" rel="stylesheet">
        <link href="assets/css/menu.css" rel="stylesheet" type="text/css">
        <link href="assets/css/style.css" rel="stylesheet">
    </head>

    <body class="sticky-header">
        <section class="bg">
            <div class="container">
                <div class="row">
                    <div class="col-lg-12 col-sm-12">
                        <div class="wrapper-page">
                            <div class="account-pages">
                                <div class="account-box">
                                    <div class="card m-b-30">
                                        <div class="card-body">
                                            <div class="card-title text-center">
                                                <h5 class="mt-3"><b>Login</b></h5>
                                            </div>  
                                            <form class="form mt-5 contact-form" method="POST">
                                                <div class="form-group ">
                                                    <div class="col-sm-12">
                                                        <input class="form-control form-control-line" type="text" placeholder="username" required="required" name="username">
                                                    </div>
                                                </div>
                                                <div class="form-group ">
                                                    <div class="col-sm-12">
                                                        <input class="form-control form-control-line" type="password" placeholder="password" required="required" name="password">
                                                    </div>
                                                </div>
                                                
                                                <div class="form-group">
                                                    <div class="col-sm-12 mt-4">
                                                        <button class="btn btn-primary btn-block" type="submit">Log In</button>
                                                    </div>
                                                </div>


                                                
                                            </form>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>

        <script src="assets/js/jquery-3.2.1.min.js"></script>
        <script src="assets/js/bootstrap.min.js"></script>
        <script src="assets/js/jquery-migrate.js"></script>
        <script src="assets/js/jquery.slimscroll.min.js"></script>

    </body>
</html>
