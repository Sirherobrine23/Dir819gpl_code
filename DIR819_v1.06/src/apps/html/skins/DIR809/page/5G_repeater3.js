var G_arrScan5 = [], G_arrRadio=[], G_arrClient=[], S_arrTemp = [];
var t=0, n=0, m=0;
var instanceTotal = 0;
var G_Idx=0;
var G_IPAddress="",G_SubMask="",G_Gateway="",G_Dns="";
<?objget :InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration. "RadioInterface Enable ConnectRootAp.SSID ConnectRootAp.BSSID ConnectRootAp.WEPKey.1.WEPKey ConnectRootAp.WEPEnctype ConnectRootAp.BasicAuthenticationMode ConnectRootAp.WEPKeyIndex ConnectRootAp.X_TWSZ-COM_WEPEncStrength ConnectRootAp.PreSharedKey.1.PreSharedKey ConnectRootAp.PreSharedKey.1.KeyPassphrase ConnectRootAp.Connect"
`	G_arrClient[m] = [];
	G_arrClient[m][0] = ":InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.$00.";	//
	G_arrClient[m][1] = "$01";	//RadioInterface
	G_arrClient[m][2] = "$02";	//Enable
	G_arrClient[m][3] = "$03";	//ConnectRootAp.SSID
	G_arrClient[m][4] = "$04";	//ConnectRootAp.BSSID
	G_arrClient[m][5] = "$05";	//ConnectRootAp.WEPKey.1.WEPKey
	G_arrClient[m][6] = "$06";	//ConnectRootAp.WEPEnctype
	G_arrClient[m][7] = "$07";	//ConnectRootAp.BasicAuthenticationMode
	G_arrClient[m][8] = "$08";	//ConnectRootAp.WEPKeyIndex
	G_arrClient[m][9] = "$09";	//ConnectRootAp.X_TWSZ-COM_WEPEncStrength
	G_arrClient[m][10] = "$0a";	//ConnectRootAp.PreSharedKey.1.PreSharedKey
	G_arrClient[m][11] = "$0b";	//ConnectRootAp.PreSharedKey.1.KeyPassphrase 
	G_arrClient[m][12] = "$0c";	//ConnectRootAp.Connect
	m++;
`?>
<?objget :InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.2.ConnectRootAp.ScanList. "SSID BSSID Channel SignalStrength EncryptionModes AuthenticationMode Standard BandWidth ExtendChannel"
`	G_arrScan5[t] = [];
	G_arrScan5[t][0] = ":InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.2.ConnectRootAp.ScanList.$00.";	
	G_arrScan5[t][1] = "$01";		                //SSID
	G_arrScan5[t][2] = "$02";						//BSSID
	G_arrScan5[t][3] = "$03";						//Channel
	G_arrScan5[t][4] = "$04";						//SignalStrength
	G_arrScan5[t][5] = "$05";						//EncryptionModes
	G_arrScan5[t][6] = "$06";                        //AuthenticationMode
	G_arrScan5[t][7] = "$07" ;                       //Standard
	G_arrScan5[t][8] = "$08";                        //BandWidth
	G_arrScan5[t][9] = "$09";                        //ExtendChannel
	++t;
`?>
<?mget :InternetGatewayDevice.LANDevice.1.LANHostConfigManagement.IPInterface.1. "IPInterfaceIPAddress IPInterfaceSubnetMask X_TWSZ-COM_BridgeGateway X_TWSZ-COM_BridgeDns"
`	G_IPAddress = "$01";
	G_SubMask 	= "$02";
	G_Gateway   = "$03";
	G_Dns       = "$04";
`?>
//var Wz_ssid=strAnsi2Unicode(Base64.Decode('<?echo $var:apSSID?>'));
var Wz_bssid='<?echo $var:apbssid?>';
var Wz_ssid='<?echo $var:apssid?>';
var Wz_mode='<?echo $var:approto?>';
var Wz_key='<?echo $var:apkey?>';
var Wz_authAlgm = "<?echo $var:apauthAlgm?>";
var Wz_keyIndex="<?echo $var:apkeyindex?>";
var Wz_wepenc = "<?echo $var:apwepenc?>";
function uiOnload(){
	setJSONValue({		
		"ip" 	: G_IPAddress,
		"mask" 	: G_SubMask,
		"gateway" : G_Gateway,
		"dns"   : G_Dns
	});
}
function forInstance(){
	var s_len5 = G_arrScan5.length;
	var instanceIdx = 0;
	
	for(instanceIdx; instanceIdx<s_len5; instanceIdx++)
	{
	    if(G_arrScan5[instanceIdx][2] == Wz_bssid)
		{
			S_arrTemp[G_Idx]=[];
			S_arrTemp[G_Idx][0] = G_arrScan5[instanceIdx][0];
			S_arrTemp[G_Idx][1] = G_arrScan5[instanceIdx][1];
			S_arrTemp[G_Idx][2] = G_arrScan5[instanceIdx][2];
			S_arrTemp[G_Idx][3] = G_arrScan5[instanceIdx][3];
			S_arrTemp[G_Idx][4] = G_arrScan5[instanceIdx][4];
			S_arrTemp[G_Idx][5] = G_arrScan5[instanceIdx][5];
			S_arrTemp[G_Idx][6] = G_arrScan5[instanceIdx][6];
			S_arrTemp[G_Idx][7] = G_arrScan5[instanceIdx][7];
			S_arrTemp[G_Idx][8] = G_arrScan5[instanceIdx][8];
		}	
	}
}
function alertError()
{
	var code=arguments[0];
    alert(code);   
}
function saveWlanChanges()
{
	if (!CheckValidity.IP("ip","Invalid IP format!"))
		return false;
	if (!CheckValidity.Mask("mask","Invalid Mask format!"))
		return false;
	if (!CheckValidity.isNetIP( $("ip").value, $("mask").value ) )
		return false;
	if(($('gateway').value == "") || ($('gateway').value == " "))
	{
		alert(SEcode['lang_gateway_invalid']);
		return false;
	}
	if (!CheckValidity.IP('gateway',SEcode['lang_gateway_invalid']))
	    return false;
	if($('gateway').value == $("ip").value)	
	{
		alertError(SEcode['lang_gw_not_same']);
		return false;
	}
	if(!isSameSubNet($("gateway").value,G_SubMask,$('ip').value,G_SubMask))
	{
		alert(SEcode["lang_gw_lan_conflict"]);	
		$("gateway").focus();
		return false;
	}
	if(($('dns').value == "") || ($('dns').value == " "))
	{
		alert(SEcode['lang_dns_invalid']);
		return false;
	}
	if (!CheckValidity.IP('dns',SEcode['lang_dns_invalid']))
	    return false;
	
	if(($('ip').value != G_IPAddress)|| ($('mask').value != G_SubMask))
	{
		var msg= SEcode["tcpiplan_dhcp_001"];
		if (!confirm(msg))
			return false;
	}
	
	$("wlrepeaterfinish5").setAttribute("disabled", true);
	
	$F(":InternetGatewayDevice.LANDevice.1.LANHostConfigManagement.DHCPServerEnable", "0");
	
	var path_Client = ":InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.2.";
	var _path_host = ":InternetGatewayDevice.LANDevice.1.LANHostConfigManagement."		
	forInstance();	
	var s_ssid    = Wz_ssid;
	var s_bssid   = S_arrTemp[G_Idx][2];
	var s_channel = S_arrTemp[G_Idx][3];
	var s_standard = S_arrTemp[G_Idx][7];
	var s_bandwith = S_arrTemp[G_Idx][8];
	var s_secmode=Wz_mode;
	$H({
		'obj-action'   : 'set',
		'var:sys_Token' : G_SysToken,
		'var:page'     : 'Wiz_wizard',
		'getpage'       : 'html/page/Wiz_wizard.ajax.js',
		'errorpage'     : 'html/page/Wiz_wizard.ajax.js'
		}, true);

		$F(path_Client + "ConnectRootAp.SSID" 					, s_ssid);
		$F(path_Client + "ConnectRootAp.BSSID" 				    , s_bssid);
		$F(path_Client + "ConnectRootAp.Standard" 				, s_standard);
		$F(path_Client + "ConnectRootAp.OperatingChannelBandwidth" 				, s_bandwith);	
		$F(path_Client + "ConnectRootAp.Channel" 					, s_channel);	
		$F(":InternetGatewayDevice.LANDevice.1.WLANConfiguration.2." + "AutoChannelEnable" , "0");
		$F(":InternetGatewayDevice.LANDevice.1.WLANConfiguration.2." + "Channel" , s_channel);
		$F(":InternetGatewayDevice.X_TWSZ-COM_Radio.2." + "AutoChannelEnable" , "0");
		$F(":InternetGatewayDevice.X_TWSZ-COM_Radio.2." + "Channel" , s_channel);
		$F(":InternetGatewayDevice.X_TWSZ-COM_Radio.2." + "Standard" , "aanac");
		$F(":InternetGatewayDevice.X_TWSZ-COM_Radio.2." + "OperatingChannelBandwidth" , "80");	

	switch(s_secmode)
	{
		case "OFF" :
			$F(path_Client + "ConnectRootAp.BeaconType" 				, 'None');
			break;
		case "WEPOPEN" :
			$F(path_Client + "ConnectRootAp.BeaconType" 				, 'Basic');
			$F(path_Client + "ConnectRootAp.BasicEncryptionModes" 		, 'WEPEncryption');
			$F(path_Client + "ConnectRootAp.BasicAuthenticationMode" 	, Wz_authAlgm);
			$F(path_Client + "ConnectRootAp.WEPKeyIndex" 				, Wz_keyIndex);
			$F(path_Client + "ConnectRootAp.WEPEnctype" 				, '0');
			var wepkeypath = "ConnectRootAp.WEPKey." + Wz_keyIndex + ".WEPKey";
			$F(path_Client + wepkeypath 			, Base64.Encode(Wz_key));
			$F(path_Client + "ConnectRootAp.X_TWSZ-COM_WEPEncStrength" , Wz_wepenc=='1'?'40-bit':'104-bit');
			break;
		case "WEPSHARE" :
			$F(path_Client + "ConnectRootAp.BeaconType" 				, 'Basic');
			$F(path_Client + "ConnectRootAp.BasicEncryptionModes" 		, 'WEPEncryption');
			$F(path_Client + "ConnectRootAp.BasicAuthenticationMode" 	, Wz_authAlgm);
			$F(path_Client + "ConnectRootAp.WEPKeyIndex" 				, Wz_keyIndex);
			$F(path_Client + "ConnectRootAp.WEPEnctype" 				, '0');
			var wepkeypath = "ConnectRootAp.WEPKey." + Wz_keyIndex+ ".WEPKey";
			$F(path_Client + wepkeypath 			, Base64.Encode(Wz_key));
			$F(path_Client + "ConnectRootAp.X_TWSZ-COM_WEPEncStrength" , Wz_wepenc=='1'?'40-bit':'104-bit');	
			break;
		case "WEPAUTO" :
		case "WEP" :
			$F(path_Client + "ConnectRootAp.BeaconType" 				, 'Basic');
			$F(path_Client + "ConnectRootAp.BasicEncryptionModes" 		, 'WEPEncryption');
			$F(path_Client + "ConnectRootAp.BasicAuthenticationMode" 	, Wz_authAlgm);
			$F(path_Client + "ConnectRootAp.WEPKeyIndex" 				, Wz_keyIndex);
			$F(path_Client + "ConnectRootAp.WEPEnctype" 				, '0');
			var wepkeypath = "ConnectRootAp.WEPKey." + Wz_keyIndex+ ".WEPKey";
			$F(path_Client + wepkeypath 			, Base64.Encode(Wz_key));
			$F(path_Client + "ConnectRootAp.X_TWSZ-COM_WEPEncStrength" , Wz_wepenc=='1'?'40-bit':'104-bit');
			break;	
		case "WPAPSKTKIP" :
			$F(path_Client + 'ConnectRootAp.BeaconType'						, 'WPA');
			$F(path_Client + 'ConnectRootAp.WPAEncryptionModes'				, 'TKIPEncryption');
			$F(path_Client + 'ConnectRootAp.WPAAuthenticationMode'				, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}		
			break;
		case "WPAPSKAES" :
			$F(path_Client + 'ConnectRootAp.BeaconType'						, 'WPA');
			$F(path_Client + 'ConnectRootAp.WPAEncryptionModes'				, 'AESEncryption');
			$F(path_Client + 'ConnectRootAp.WPAAuthenticationMode'				, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}			
			break;
		case "WPAPSKTKIPAES" :
			$F(path_Client + 'ConnectRootAp.BeaconType'						, 'WPA');
			$F(path_Client + 'ConnectRootAp.WPAEncryptionModes'				, 'TKIPandAESEncryption');
			$F(path_Client + 'ConnectRootAp.WPAAuthenticationMode'				, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}		
			break;	
		case "WPA2PSKTKIP" :
			$F(path_Client + 'ConnectRootAp.BeaconType'						, '11i');
			$F(path_Client + 'ConnectRootAp.IEEE11iEncryptionModes'			, 'TKIPEncryption');
			$F(path_Client + 'ConnectRootAp.IEEE11iAuthenticationMode'			, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}
			break;
		case "WPA2PSKAES" :
			$F(path_Client + 'ConnectRootAp.BeaconType'						, '11i');
			$F(path_Client + 'ConnectRootAp.IEEE11iEncryptionModes'			, 'AESEncryption');
			$F(path_Client + 'ConnectRootAp.IEEE11iAuthenticationMode'			, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}
			break;	
		case "WPA2PSKTKIPAES" :
			$F(path_Client + 'ConnectRootAp.BeaconType'						, '11i');
			$F(path_Client + 'ConnectRootAp.IEEE11iEncryptionModes'			, 'TKIPandAESEncryption');
			$F(path_Client + 'ConnectRootAp.IEEE11iAuthenticationMode'			, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}
			break;	
		case "WPAPSKWPA2PSKTKIP" :
			$F(path_Client_5G + 'ConnectRootAp.BeaconType'						, 'WPAand11i');
			$F(path_Client_5G + 'ConnectRootAp.WPAEncryptionModes'				, 'TKIPEncryption');
			$F(path_Client_5G + 'ConnectRootAp.WPAAuthenticationMode'				, 'PSKAuthentication');
			$F(path_Client_5G + 'ConnectRootAp.IEEE11iEncryptionModes'			, 'TKIPEncryption');
			$F(path_Client_5G + 'ConnectRootAp.IEEE11iAuthenticationMode'			, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}
			break;
		case "WPAPSKWPA2PSKAES" :
			$F(path_Client + 'ConnectRootAp.BeaconType'						, 'WPAand11i');
			$F(path_Client + 'ConnectRootAp.WPAEncryptionModes'				, 'AESEncryption');
			$F(path_Client + 'ConnectRootAp.WPAAuthenticationMode'				, 'PSKAuthentication');
			$F(path_Client + 'ConnectRootAp.IEEE11iEncryptionModes'			, 'AESEncryption');
			$F(path_Client + 'ConnectRootAp.IEEE11iAuthenticationMode'			, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}
			break;	
		case "WPAPSKWPA2PSKTKIPAES" :
			$F(path_Client + 'ConnectRootAp.BeaconType'						, 'WPAand11i');
			$F(path_Client + 'ConnectRootAp.WPAEncryptionModes'				, 'TKIPandAESEncryption');
			$F(path_Client + 'ConnectRootAp.WPAAuthenticationMode'				, 'PSKAuthentication');
			$F(path_Client + 'ConnectRootAp.IEEE11iEncryptionModes'			, 'TKIPandAESEncryption');
			$F(path_Client + 'ConnectRootAp.IEEE11iAuthenticationMode'			, 'PSKAuthentication');
			if(Wz_key.length == 64){
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.PreSharedKey'	, Base64.Encode(Wz_key));
			}else{
				$F(path_Client + 'ConnectRootAp.PreSharedKey.1.KeyPassphrase'	, Base64.Encode(Wz_key));
			}
			break;			
		default :
			alert(s_secmode);
			alert("Not support this Auth type yet!");
	}
	var _url = "/cgi-bin/webproc";
	G_ajax = Ajax.getInstance(_url, "", 0, doConn, null_errorfunc);
	G_ajax.post($('uiPostForm'));
}
function doConn(_json){
	try {
		eval(_json);
	}catch(e){
		return false;
	}
	
	G_SysToken=G_SysToken_ajax;
	
	if(G_Error == '1')
	{
		dealErrorMsgToken(G_Error_Msg);
		dealWithError();
	}else
	{
		saveIPChanges();
	}
}

function null_errorfunc(){
	return true;
}

function saveIPChanges()
{
	var _path_ipif = ":InternetGatewayDevice.LANDevice.1.LANHostConfigManagement.IPInterface."	
	if(($('ip').value != G_IPAddress)|| ($('mask').value != G_SubMask))
	{		
		$H({
			"obj-action" 		: "set",
			"getpage" 			: "html/page/restarting3.html",
			"errorpage" 		: "html/index.html",
			"var:menu" 			: G_Menu,
			"var:page" 			: "Bas_lan",
			"var:sys_Token"     : G_SysToken,
			"var:CacheLastData" : ViewState.Save()
		}, true);			
	}else{
		$H({
			"obj-action" 		: "set",
			"getpage" 			: "html/page/restarting2.html",
			"errorpage" 		: "html/index.html",
			"var:menu" 			: "home",
			"var:page" 			: "Hom_status",
			"var:sys_Token"     : G_SysToken,
			"var:errorpage" 	: "Hom_status",
			"var:CacheLastData" : ViewState.Save()
		}, true);		
	}	
	// ip address
	$F( _path_ipif + '1.IPInterfaceIPAddress'		, $('ip').value );
	$F( _path_ipif + '1.IPInterfaceSubnetMask'		, $('mask').value );
	$F( _path_ipif + '1.X_TWSZ-COM_BridgeGateway'	, $('gateway').value );
	$F( _path_ipif + '1.X_TWSZ-COM_BridgeDns'		, $('dns').value );
	$('uiPostForm').submit();
}
function dealWithError(){
	if (G_Error != 1){
		return false;
	}

	dealErrorMsg({}, G_Error_Msg);
	
		}
		
addListeners(uiOnload, dealWithError);
