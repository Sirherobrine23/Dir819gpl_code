var G_arrScan5 = [], G_arrRadio=[], G_arrClient=[], S_arrTemp = [];
var t=0, n=0, m=0;
var instanceTotal = 0;
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
	G_arrScan5[t][0] = ":InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.1.ConnectRootAp.ScanList.$00.";	
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
var apBSSID ='<?echo $var:apbssid?>';
var apSSID='<?echo $var:apssid?>';
var apMode='<?echo $var:approto?>';
function uiOnload(){
		var approto = apMode;
		if(approto=="WEPOPEN"||approto=="WEPSHARE"||approto=="WEPAUTO")
			approto="WEP";
		else if(approto=="WPAPSKTKIP")
			approto="WPA-PSK[TKIP]";
		else if(approto=="WPAPSKAES"||approto=="WPAPSKTKIPAES")
			approto="WPA-PSK[AES]";
		else if(approto=="WPA2PSKTKIP")
			approto="WPA2-PSK[TKIP]";
		else if(approto=="WPA2PSKAES"||approto=="WPA2PSKTKIPAES")
			approto="WPA2-PSK[AES]";
		else if(approto=="WPAPSKWPA2PSKTKIP")
			approto="WPA2-PSK[TKIP]";
		else if(approto=="WPAPSKWPA2PSKAES"||approto=="WPAPSKWPA2PSKTKIPAES")
			approto="WPA2-PSK[AES]";
		$('method').value = approto;
		Securitytype(approto);
}
function Securitytype(opt_id)
{
	if(opt_id=="OFF")
	{
		$('SEL_wpa').style.display = "none";
		$('SEL_wep').style.display = "none";
	}
	else if(opt_id=="WEP")
	{
		$('SEL_wpa').style.display = "none";
		$('SEL_wep').style.display = "";
		Form.Radio('defaultTxKeyId', 1);
		
  		setJSONValue({
		'show_key1'	:'',
		'show_key2'	:'',
		'show_key3'	:'',
		'show_key4'	:''
		});
		
		setKeys();
	}
	else 
	{
		$('SEL_wpa').style.display = "";
		$('SEL_wep').style.display = "none";
		setJSONValue({'show_pskValue'	: ''});
	}
}
function setKeys()
{
	var cf=$('length');

	if (cf.selectedIndex == 0)
    {    
        var keysize = 10;
        $('show_key1').size = $('show_key2').size = $('show_key3').size = $('show_key4').size = keysize + 5 ; // extra for Mac
        if ($('show_key1').value.length>10)
            $('show_key1').value = $('show_key1').value.substring(0,10);
        if ($('show_key2').value.length>10)
            $('show_key2').value = $('show_key2').value.substring(0,10);
        if ($('show_key3').value.length>10)
            $('show_key3').value = $('show_key3').value.substring(0,10);
        if ($('show_key4').value.length>10)
            $('show_key4').value = $('show_key4').value.substring(0,10);
			
		$('show_key1').maxLength=10;
		$('show_key2').maxLength=10;
		$('show_key3').maxLength=10;
		$('show_key4').maxLength=10;
    }
    else if(cf.selectedIndex == 1)
    {     
        var keysize = 26;
        $('show_key1').size = $('show_key2').size = $('show_key3').size = $('show_key4').size = keysize + 15 ; // extra for Mac
        if ($('show_key1').value.length>26)
            $('show_key1').value = $('show_key1').value.substring(0,26);
        if ($('show_key2').value.length>26)
            $('show_key2').value = $('show_key2').value.substring(0,26);
        if ($('show_key3').value.length>26)
            $('show_key3').value= $('show_key3').value.substring(0,26);
        if ($('show_key4').value.length>26)
            $('show_key4').value = $('show_key4').value.substring(0,26);
			
		$('show_key1').maxLength=26;
		$('show_key2').maxLength=26;
		$('show_key3').maxLength=26;
		$('show_key4').maxLength=26;
    }
    else if(cf.selectedIndex == 2)
    {
        var keysize = 32;
         $('show_key1').size = $('show_key2').size = $('show_key3').size = $('show_key4').size = keysize + 2 ;// extra for Mac
    }
}

function CheckData()
{	
	if ((apMode == "WPAPSKTKIP") || (apMode == "WPAPSKAES") || (apMode == "WPAPSKTKIPAES") || (apMode == "WPA2PSKTKIP") || (apMode == "WPA2PSKAES") || (apMode == "WPA2PSKTKIPAES") || (apMode == "WPAPSKWPA2PSKTKIP")|| (apMode == "WPAPSKWPA2PSKAES") || (apMode == "WPAPSKWPA2PSKTKIPAES"))
		return CheckData_WPA($("show_pskValue"));
	else if(apMode =="WEP" || apMode =="WEPOPEN" || apMode =="WEPSHARE" || apMode =="WEPAUTO")
		return CheckData_WEP($("length"), document.getElementsByName("defaultTxKeyId"), "show_key", $("show_key1"), $("show_key2"), $("show_key3"), $("show_key4"));
	else
		return true;	
}

function CheckData_WPA(passphrase)
{
    if(passphrase.value.length < 8)
    {
        alert("A passphrase consists of either 8~63 ASCII characters or exactly 64 hex-digits. A hex digit is one of these characters: 0, 1, 2, ..., 8, 9, A, B, C, D, E, F.");
        passphrase.focus();
        return false;    
    }
    if(passphrase.value.length > 63)
    {
        if ( isHex(passphrase.value) == false)
        {
            alert("A passphrase consists of either 8~63 ASCII characters or exactly 64 hex-digits. A hex digit is one of these characters: 0, 1, 2, ..., 8, 9, A, B, C, D, E, F.");
            //passphrase.value = "";
            passphrase.focus();
            return false;
        }    
    }
    
    if (passphrase.value.match( /[^\x20-\x7E]/ ))
    {
        alert("Character is not allowed in passphrase.");
        passphrase.focus();
        return false;
    }
    
    return true;
}
function CheckData_WEP(wepenc, wep_key_no, key, key1, key2, key3, key4)
{
    var msg_key64_type = "Invalid Key.Keys length should be 10 Hex (0~9 and A~F) chars or 5 ASCII chars.";
    var msg_key128_type = "Invalid Key.Keys length should be 26 Hex (0~9 and A~F) chars or 13 ASCII chars.";
    
    var msg = ""; var blankFlag = false; var sizeOK = false; var i;
    var len = (wepenc.selectedIndex==0)?10:((wepenc.selectedIndex==1)?26:32);
    for (i = 1; i < 5; i++ )
    {
        msg = "";
        blankFlag = ! (eval(wep_key_no[i-1].checked)); // default key
        if( (blankFlag) && (eval("(key"+ i + ".value.length == 0)")) )
            continue; // blank ok
        sizeOK = (((eval("isHex(key" + i +".value)")) && (eval("(key" + i + ".value.length == len)"))) || (eval("(key" + i + ".value.length == len/2)")));
        if (!sizeOK)
        {
            msg += (len == 10)?msg_key64_type:msg_key128_type;
            alert(msg);
            if (i==1)
                key1.focus();
            else if (i==2)
                key2.focus();
            else if (i==3)
                key3.focus();
            else if (i==4)
                key4.focus();
            return false;
        }
    }
    
    return true;
}
function isHex(str) {
    var i;
    for(i = 0; i<str.length; i++) {
        var c = str.substring(i, i+1);
        if(("0" <= c && c <= "9") || ("a" <= c && c <= "f") || ("A" <= c && c <= "F")) {
            continue;
        }
        return false;
    }
    return true;
}
function onClickScanUplinkApNext()
{		
	if(CheckData() == false)
		return false;
	var apKey="",apKeyindex="",authAlgm="",wepenc="";
	if($("method").value == "WEP")
	{
		var key="";
		var keyindex=0;

		var opt_id = $('length').value;
		if(opt_id=="1")
		{
			apKeyindex = Form.Radio('defaultTxKeyId');
			var index="show_key" + apKeyindex;
			apKey = $(index).value;
			wepenc = '1';
		}
		else
		{
			apKeyindex = Form.Radio('defaultTxKeyId');
			var index="show_key" + apKeyindex;
			apKey = $(index).value;
			wepenc = '2';
		}
		authAlgm= $('authType').value;
	}
	else if($("method").value != "OFF")
	{
		apKey= $('show_pskValue').value;	
	}
	$G('/cgi-bin/webproc',{
		    'var:apbssid'          : apBSSID,
			'var:apssid'		: apSSID,
			'var:approto'		: apMode,	
			'var:apkey'			: apKey,
			'var:apkeyindex'	: apKeyindex,	
			'var:apauthAlgm'	: authAlgm,	
			'var:apwepenc'		: wepenc,
			'var:sys_Token' : G_SysToken,
			'var:page'		: '5G_repeater3',
			'var:menu'		: 'basic',
			'getpage'		: 'html/index.html',
			'errorpage'		: 'html/index.html'
		});
}
function dealWithError(){
	if (G_Error != 1){
		return false;
	}

	dealErrorMsg({}, G_Error_Msg);
	
		}
		
addListeners(uiOnload, dealWithError);
