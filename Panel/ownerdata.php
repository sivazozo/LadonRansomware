<?php
include_once("config.php");
if(!empty($_GET['chat'])){
														$contactid = $_GET['chat'];

                                                        $chat = "SELECT * FROM `chat` WHERE `contactid` = :contactid";
                                                        if($sth = $db->prepare($chat)){
                                                            $sth->bindParam(':contactid', $contactid);
                                                            $sth->execute();
                                                          if($sth->rowCount() > 0 ){
                                                            
                                                            while( $row = $sth->fetch(PDO::FETCH_ASSOC) ) {
                                                               if($row["admin"] == "1"){
                                                                    echo "You: ";
                                                                }
                                                                else{
                                                                    echo "Victim: ";
                                                                }
                                                                echo htmlentities($row["message"], ENT_QUOTES);
                                                                echo "\n";
                                                            }
                                                          }
                                                        }
}



else if(!empty($_GET['comment'])){
$contactid = $_GET['comment'];
if(!empty($_POST['message'])){

$message = $_POST['message'];
$insertmsg = "INSERT INTO `chat` (`contactid`, `message`, `day`, `admin`) VALUES (:contactid, :message, NOW(), '1')";
if($sth = $db->prepare($insertmsg)){
	$sth->bindParam(':contactid', $contactid);
	$sth->bindParam(':message', $message);
	$sth->execute();
}

}
else{
	echo "Empty Message Was Not Sent!";
}

}


else {
"Snoop much?";
}
?>
