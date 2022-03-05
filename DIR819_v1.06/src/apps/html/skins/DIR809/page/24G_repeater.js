var G_arrScan2 = [], G_arrRadio=[], G_arrClient=[], S_arrTemp = [];
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
<?objget :InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.1.ConnectRootAp.ScanList. "SSID BSSID Channel SignalStrength EncryptionModes AuthenticationMode Standard BandWidth ExtendChannel"
`	G_arrScan2[t] = [];
	G_arrScan2[t][0] = ":InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.1.ConnectRootAp.ScanList.$00.";	
	G_arrScan2[t][1] = "$01";		                //SSID
	G_arrScan2[t][2] = "$02";						//BSSID
	G_arrScan2[t][3] = "$03";						//Channel
	G_arrScan2[t][4] = "$04";						//SignalStrength
	G_arrScan2[t][5] = "$05";						//EncryptionModes
	G_arrScan2[t][6] = "$06";                        //AuthenticationMode
	G_arrScan2[t][7] = "$07" ;                       //Standard
	G_arrScan2[t][8] = "$08";                        //BandWidth
	G_arrScan2[t][9] = "$09";                        //ExtendChannel
	++t;
`?>
var Wz_startscan = '<?echo $var:Startscan?>';
function uiOnload(){
	setJSONValue({
				'RepeaterSSID'   : G_arrClient[0][3]
			});
	if(Wz_startscan == '1')
	{
		crtNetWorkList();
		$("SEL_SCAN").style.display = "block";
	}
}

var scanTimes = 0;
function uiScan(){
/*
	if((G_arrClient[0][2] == "0") )
	{		
		if (confirm("DHCP mode will be set to 'none' if the repeater is enabled.Be sure to enable repeater?") == 0)
		{			
			return false;
		}
	}
*/
	Table.Clear("TB_NetworkList");
	scanTimes = 0;
	scanAp();
}

function scanAp()
{	
	wtime = 15;//wtime initial value
	$("RepeaterSSID").disabled = true;
	$("scanUplink2G").disabled = true;
	$("scanUplink2G_tip").style.display = "block";
	$("SEL_SCAN").style.display = "none";
	// set flag to '2', and then submit
	timerStart();
	var tempPath = G_arrClient[0][0]+'ApCliTriggerScan';
	var _path_host = ":InternetGatewayDevice.LANDevice.1.LANHostConfigManagement."		

	$H({
		'obj-action' 	: 'set',
		'var:menu' 		: G_Menu,
		'var:sys_Token' : G_SysToken,
		'var:page' 		: G_Page,
		'var:errorpage' : G_Page,
		'getpage' 		: 'html/page/apupscan.ajax.js'
	},true);
	
	$F(tempPath, '1');
	$F(":InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.1.Enable", '1');
	$F(_path_host + "DHCPServerEnable" 					, "0");

	var _url = "/cgi-bin/webproc";
	ajax = Ajax.getInstance(_url, "", 0, getScan, null_errorfunc);
	ajax.post($('uiPostForm'));		
}
function null_errorfunc(){
	return true;
}

function getScan(responseText){
	try {
		eval(responseText);
	}catch(e){}
	
	G_SysToken=G_SysToken_ajax;
	
	if(G_AplistUpdate == '0'){
		setTimeout('doScan()', 2000);
	}else if(G_AplistUpdate == '1'){
	}else{
		if(scanTimes < 3){
			scanTimes++;
			scanAp();
		}else{
		}
	}
}

function doScan(){
	var _url = "/cgi-bin/webproc?getpage=html/page/apupscan.ajax.js&var:page=*";
	ajax = Ajax.getInstance(_url, "", 0, getScan,null_errorfunc);
	ajax.get();
}

function reloadPage(responseText){
	try {
		eval(responseText);
	}catch(e){}
    
	if(G_AplistUpdate == '0'){
		setTimeout('doScan()', 2000);
	}else if(G_AplistUpdate == '1'){
		uiPageRefresh();
	}else if(G_AplistUpdate == '2'){
		//ctrShow("ScanFail");
	}
}

function checkSpace(id) {
	if (document.getElementById(id).value.length == 0) 
		return false;
	if (document.getElementById(id).value.indexOf(" ",0) == 0 || document.getElementById(id).value.lastIndexOf(" ") ==
	 (document.getElementById(id).value.length -1)) {
		return true;
	}
}
var G_frequency = "2.4G";
function crtNetWorkList(){
	var s_len2 = G_arrScan2.length;
	var instanceIdx = 0;	
	var secMOde="";
	for(instanceIdx; instanceIdx<s_len2; instanceIdx++)
	{
		S_arrTemp[instanceIdx]=[];
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][0]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][1]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][2]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][3]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][4]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][5]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][6]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][7]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][8]);
		S_arrTemp[instanceIdx].push(G_arrScan2[instanceIdx][9]);
		instanceTotal++;			
	}
	
	S_arrTemp.sort(sortFunction);
	var G_arrScan=[];
	for(var j=0; j<instanceTotal; j++){
		G_arrScan[j]=[];
		G_arrScan[j].push(j+1);
		G_arrScan[j].push(S_arrTemp[j][1]);
		G_arrScan[j].push(S_arrTemp[j][2].toUpperCase());
		G_arrScan[j].push(S_arrTemp[j][3]);
		G_arrScan[j].push(S_arrTemp[j][4]+'%');
		if(S_arrTemp[j][6]=="NONE")
		{
            if(S_arrTemp[j][5]=="NONE")
			{
				secMOde = "OFF";
				S_arrTemp[j][10]="OFF";
			}
		}
		else if(S_arrTemp[j][6]=="WEP")
		{
			if(S_arrTemp[j][5]=="NONE")
			{
				secMOde = "WEP";
				S_arrTemp[j][10]="WEPAUTO";
			}
	        else if(S_arrTemp[j][5]=="OPEN")
			{
				secMOde = "WEP";
				S_arrTemp[j][10]="WEPOPEN";
			}
            else if(S_arrTemp[j][5]=="SHARED")
			{
				secMOde = "WEP";
				S_arrTemp[j][10]="WEPSHARE";
			}
            else if(S_arrTemp[j][5]=="AUTOWEP")
			{
				secMOde = "WEP";
				S_arrTemp_5G[j][10]="WEPAUTO";
			}			
		}
		else if(S_arrTemp[j][6]=="WPAPSK")
		{
            if(S_arrTemp[j][5]=="TKIPEncryption")
			{
				secMOde = "WPA-PSK";
				S_arrTemp[j][10]="WPAPSKTKIP";
			}
			else if(S_arrTemp[j][5]=="AESEncryption")
			{
				secMOde = "WPA-PSK";
				S_arrTemp[j][10]="WPAPSKAES";
			}
			else if(S_arrTemp[j][5]=="TKIPandAESEncryption")
			{
				secMOde = "WPA-PSK";
				S_arrTemp[j][10]="WPAPSKTKIPAES";
			}
		}
		else if(S_arrTemp[j][6]=="WPA2PSK")
		{
            if(S_arrTemp[j][5]=="TKIPEncryption")
			{
				secMOde = "WPA2-PSK";
				S_arrTemp[j][10]="WPA2PSKTKIP";
			}
			else if(S_arrTemp[j][5]=="AESEncryption")
			{
				secMOde = "WPA2-PSK";
				S_arrTemp[j][10]="WPA2PSKAES";
			}
			else if(S_arrTemp[j][5]=="TKIPandAESEncryption")
			{
				secMOde = "WPA2-PSK";
				S_arrTemp[j][10]="WPA2PSKTKIPAES";
			}
		}
		else if(S_arrTemp[j][6]=="WPA1PSKWPA2PSK")
		{
            if(S_arrTemp[j][5]=="TKIPEncryption")
			{
				secMOde = "WPA/WPA2-PSK";
				S_arrTemp[j][10]="WPAPSKWPA2PSKTKIP";
			}
			else if(S_arrTemp[j][5]=="AESEncryption")
			{
				secMOde = "WPA/WPA2-PSK";
				S_arrTemp[j][10]="WPAPSKWPA2PSKAES";
			}
			else if(S_arrTemp[j][5]=="TKIPandAESEncryption")
			{
				secMOde = "WPA/WPA2-PSK";
				S_arrTemp[j][10]="WPAPSKWPA2PSKTKIPAES";
			}
		}
		G_arrScan[j].push(secMOde);
		G_arrScan[j].push("<input type='radio' name='RAD_SEL' id='RAD_SEL_"+ j +"' value='"+ j + "' onClick='uiNextStatusChange();'>");
	}
	var G_style=['center','left','center','center','center'];
	$T("TB_NetworkList", G_arrScan,'1',G_style);
}
function sortFunction(x, y){
	return y[4] - x[4];
}
function uiNextStatusChange()
{
	var index = Form.Radio('RAD_SEL');
	$("RepeaterSSID").value = S_arrTemp[index][1];
}

function onClickScanUplinkApNext()
{
	var index = Form.Radio('RAD_SEL');
	if("" == $("RepeaterSSID").value) 
	{
		//alert('SSID cannot be empty!');
		//alert(SEcode['lang_invalid_input'])
		alert(SEcode['lang_ssid_empty']);
		$("RepeaterSSID").focus();
		return false;
	}
	if( index == undefined){
		alert('Please select a wireless SSID from the list!');
	}
	if($("RepeaterSSID").value.match(/[\|%&;\$@\+><\?\(\)]/))
	{			
		alert('Error. The input cannot contain the following illegal characters,such as @ | % & ; $ + > < ? ( ) !');
		return false;	
	}
	var apbssid,apssid="", approto="";

	    apbssid = S_arrTemp[index][2];
	    apssid= $("RepeaterSSID").value;
		//apssid=Base64.Encode(xss_replace(apssid));
		approto = index==undefined?"OFF":S_arrTemp[index][10];
		
	$G('/cgi-bin/webproc',{
		    'var:apbssid'          : apbssid,
			'var:apssid'		: apssid,
			'var:approto'		: approto,			
			'var:page'		: '24G_repeater2',
			'var:menu'		: 'basic',
			'var:sys_Token' : G_SysToken,
			'getpage'		: 'html/index.html',
			'errorpage'		: 'html/index.html'
		});
}

function charTraslt(pValue){
	return pValue.replace(/&/gi, "&#38;").replace(/</gi, "&lt;").replace(/>/gi, "&gt;");
}
var wtime;
function timerStart() 
{ 
	if (wtime >= 0)
	{ 
		$("scanUplink2G_time").innerText = wtime;

		//$("scanUplinkAp").value = "Surveying, please don't interrupt, remaining "+wtime+" s";
		wtime--;
		setTimeout("timerStart()",1000);
	}
	else
	{
		$("scanUplink2G_tip").style.display = "none";
		top.document.location.href="/cgi-bin/webproc?getpage=html/index.html&var:menu=basic&var:page=24G_repeater&var:Startscan=1";
	}
}

function dealWithError(){
	if (G_Error != 1){
		return false;
	}

	dealErrorMsg({}, G_Error_Msg);
	
		}
		
addListeners(uiOnload, dealWithError);
