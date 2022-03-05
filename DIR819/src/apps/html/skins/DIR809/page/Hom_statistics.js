/*  JavaScript Document:Hom_statistics  */
/*---  WLAN  ---*/
var G_WirelessStatus = [];
var m = 0;
<?objget :InternetGatewayDevice.LANDevice.1.WLANConfiguration. "Enable TotalBytesSent TotalBytesReceived TotalPacketsSent TotalPacketsReceived Stats.ErrorsReceived Stats.ErrorsSent Stats.DiscardPacketsReceived Stats.DiscardPacketsSent SSID Stats.TotalColls"
`	G_WirelessStatus[m] = [];
	G_WirelessStatus[m][0] = "$01"; //Enable
	G_WirelessStatus[m][1] = "$02"; //byteSent
	G_WirelessStatus[m][2] = "$03"; //BytesReceive
	G_WirelessStatus[m][3] = "$04"; //PacketsSent
	G_WirelessStatus[m][4] = "$05"; //PacketsReceived
	G_WirelessStatus[m][5] = "$06"; //RxError
	G_WirelessStatus[m][6] = "$07"; //TxError
	G_WirelessStatus[m][7] = "$08"; //RxDrop
	G_WirelessStatus[m][8] = "$09"; //TxDrop
	G_WirelessStatus[m][9] = "$0a"; //SSID
	G_WirelessStatus[m][10] = "$0b"; //TotalColls
	m++;
`?>
/*---  LAN  ---*/
var G_LanStatus = [];
var m = 0;
<?objget :InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig. "Status Stats.BytesSent Stats.BytesReceived Stats.PacketsSent Stats.PacketsReceived Stats.RxError Stats.TxError Stats.RxDrop Stats.TxDrop"
`	G_LanStatus[m] = [];
	G_LanStatus[m][0] = "$01"; //status
	G_LanStatus[m][1] = "$02"; //bytesSent
	G_LanStatus[m][2] = "$03"; //BytesReceived
	G_LanStatus[m][3] = "$04"; //PacketsSent
	G_LanStatus[m][4] = "$05"; //PacketsReceived
	G_LanStatus[m][5] = "$06"; //RxError
	G_LanStatus[m][6] = "$07"; //TxError
	G_LanStatus[m][7] = "$08"; //RxDrop
	G_LanStatus[m][8] = "$09"; //TxDrop
	m++;
`?>

/*---  WAN  ---*/
//Wan Conns List
var G_WanConns = [];
var m = 0;
<?objget :InternetGatewayDevice.WANDevice.1.WANConnectionDevice. "WANIPConnectionNumberOfEntries WANPPPConnectionNumberOfEntries"
`	<?if gt $11 0
	`	<?objget :InternetGatewayDevice.WANDevice.1.WANConnectionDevice.$20.WANIPConnection. "Name ConnectionType AddressingType ConnectionStatus Stats.EthernetBytesReceived Stats.EthernetPacketsReceived Stats.EthernetDiscardPacketsReceived Stats.EthernetErrorsReceived Stats.EthernetBytesSent Stats.EthernetPacketsSent Stats.EthernetDiscardPacketsSent Stats.EthernetErrorsSent"
		`	G_WanConns[m] = ["InternetGatewayDevice.WANDevice.$30.WANConnectionDevice.$20.WANIPConnection.$00.", //Path
					 "$01",   	//name
					 "$02",		//connection type
					 "$03",		//address type
                     "$04",     //ConnectionStatus
					 "$05",		//r_byte
					 "$06",		//r_pkts
					 "$07",		//r_drop
					 "$08",		//r_error
					 "$09",		//t_type
					 "$0a",		//t_pkts
					 "$0b",		//t_drop
					 "$0c"		//t_error
					];			
			G_WanConns[m].push("<?get :InternetGatewayDevice.WANDevice.1.WANConnectionDevice.$30.WANIPConnection.$10.X_TWSZ-COM_IPv6Config.ConnectionStatus ?>");
			++m;
		`?>
	`?>
	<?if gt $12 0
	`	<?objget :InternetGatewayDevice.WANDevice.1.WANConnectionDevice.$20.WANPPPConnection. "Name ConnectionType ConnectionStatus Stats.EthernetBytesReceived Stats.EthernetPacketsReceived Stats.EthernetDiscardPacketsReceived Stats.EthernetErrorsReceived Stats.EthernetBytesSent Stats.EthernetPacketsSent Stats.EthernetDiscardPacketsSent Stats.EthernetErrorsSent"
		`	G_WanConns[m] = ["InternetGatewayDevice.WANDevice.$30.WANConnectionDevice.$20.WANPPPConnection.$00.", //Path
					 "$01",   	//name
					 "$02" ,    //connection type
					 "pppoe",   //address type
                     "$03",     //ConnectionStatus
					 "$04",	 	//r_byte
					 "$05",     //r_pkts
					 "$06",		//r_drop
					 "$07",		//r_error
					 "$08",		//t_type
					 "$09",		//t_pkts
					 "$0a",		//t_drop
					 "$0b"		//t_error
					 ];
			G_WanConns[m].push("<?get :InternetGatewayDevice.WANDevice.1.WANConnectionDevice.$30.WANPPPConnection.$10.X_TWSZ-COM_IPv6Config.ConnectionStatus ?>");
			++m;
		`?>
	`?>
`?>

//初始化
function uiOnload(){
	crtWlan24Table();
	crtWlan5Table();
	ctrLANTable();	
	ctrWANTable();
}
//WLAN Table
function crtWlan24Table(){
	setJSONValue({ 
			'lang_wlan24_sent'       : G_WirelessStatus[0][3],
			'lang_wlan24_received'   : G_WirelessStatus[0][4],
			'lang_wlan24_txdropped'  : G_WirelessStatus[0][8],
			'lang_wlan24_rxdropped'  : G_WirelessStatus[0][7],
			'lang_wlan24_collisions' : G_WirelessStatus[0][10],
			'lang_wlan24_errors'     : Number(G_WirelessStatus[0][5])+Number(G_WirelessStatus[0][6])
		});
}
function crtWlan5Table(){
	setJSONValue({ 
			'lang_wlan5_sent'       : G_WirelessStatus[1][3],
			'lang_wlan5_received'   : G_WirelessStatus[1][4],
			'lang_wlan5_txdropped'  : G_WirelessStatus[1][8],
			'lang_wlan5_rxdropped'  : G_WirelessStatus[1][7],
			'lang_wlan5_collisions' : G_WirelessStatus[1][10],
			'lang_wlan5_errors'     : Number(G_WirelessStatus[1][5])+Number(G_WirelessStatus[1][6])
		});
}
//LAN Table
function ctrLANTable(){
	setJSONValue({ 
			'lang_lan_sent'       : G_LanStatus[0][3],
			'lang_lan_received'   : G_LanStatus[0][4],
			'lang_lan_txdropped'  : G_LanStatus[0][8],
			'lang_lan_rxdropped'  : G_LanStatus[0][7],
			'lang_lan_collisions' : '0',
			'lang_lan_errors'     : Number(G_LanStatus[0][5])+Number(G_LanStatus[0][6])
		});
}
//WAN Table
function ctrWANTable(){
	setJSONValue({ 
			'lang_wan_sent'       : G_WanConns[0][10],
			'lang_wan_received'   : G_WanConns[0][6],
			'lang_wan_txdropped'  : G_WanConns[0][11],
			'lang_wan_rxdropped'  : G_WanConns[0][7],
			'lang_wan_collisions' : '0',
			'lang_wan_errors'     : Number(G_WanConns[0][8])+Number(G_WanConns[0][12])
		});
}

//监听加载
addListeners(uiOnload);