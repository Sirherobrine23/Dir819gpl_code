var G_Mode = "<?get :InternetGatewayDevice.X_TWSZ-COM_Radio.1.DeviceOperationMode?>";
var repeater_24G = "<?get :InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.1.Enable?>";
var repeater_5G = "<?get :InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.2.Enable?>";
var G_Wireless = [];
var n = 0;
 <?objget :InternetGatewayDevice.LANDevice.1.WLANConfiguration. "BeaconType WPAAuthenticationMode IEEE11iAuthenticationMode"
        `	
            G_Wireless[n] = ['InternetGatewayDevice.LANDevice.1.WLANConfiguration.$00.', //path
                     '$01', //BeaconType
					 '$02', //WPAAuthenticationMode
					 '$03', //IEEE11iAuthenticationMode
                     ];
             n++;
`?>

function uiOnload(){	
	G_Mode == "WirelessRepeater"?$("repeater_band").style.display = "block":$("repeater_band").style.display = "none";
	
	$("device_mode").value = G_Mode;
	if(repeater_24G == "1"){
		Form.Radio("band_type", "1");
	}else if(repeater_5G == "1"){
		Form.Radio("band_type", "0");
	}
}
function uiSubmit()
{
	if($("device_mode").value!= G_Mode)
	{	
	    if($("device_mode").value == "WirelessRepeater"){
			console.log("G_Wireless[0][1]"+G_Wireless[0][1]+",G_Wireless[0][2]="+G_Wireless[0][2]+","+G_Wireless[0][3]);
			console.log("G_Wireless[1][1]"+G_Wireless[1][1]+",G_Wireless[1][2]="+G_Wireless[1][2]+","+G_Wireless[1][3]);
			var enterMode_24 = ((G_Wireless[0][1]=="WPA"&&G_Wireless[0][2]!="PSKAuthentication")||(G_Wireless[0][1]=="11i"&&G_Wireless[0][3]!="PSKAuthentication")||(G_Wireless[0][1]=="WPAand11i"&&G_Wireless[0][3]!="PSKAuthentication"));
			var enterMode_5 =  ((G_Wireless[1][1]=="WPA"&&G_Wireless[1][2]!="PSKAuthentication")||(G_Wireless[1][1]=="11i"&&G_Wireless[1][3]!="PSKAuthentication")||(G_Wireless[1][1]=="WPAand11i"&&G_Wireless[1][3]!="PSKAuthentication"));
			if(enterMode_24 || enterMode_5){
				alert(SEcode['lang_switchrepeater_invalid']);
		        return false;
			}
		}
		if(confirm(SEcode['lang_modechange_warning'])==false)
		{
			return false;
		}

		$H({
				"obj-action" 	: "set",
				'var:menu'      : G_Menu,
				'var:page'      : G_Page,
				'var:sys_Token' : G_SysToken,
				'var:errorpage' : G_Page,
				'getpage'       : 'html/page/restarting3.html',
				'errorpage'     : 'html/index.html',
				'var:CacheLastData' : ViewState.Save()
			},true);	          	
	}
	else
	{
		$H({
			"obj-action" 	: "set",
			'var:menu'      : G_Menu,
			'var:page'      : G_Page,
			'var:sys_Token' : G_SysToken,
			'var:errorpage' : G_Page,
			'getpage'       : 'html/index.html',
			'errorpage'     : 'html/index.html',
			'var:CacheLastData' : ViewState.Save()
			},true);	
	}	
	$H({
		':InternetGatewayDevice.X_TWSZ-COM_Radio.1.DeviceOperationMode'    : $("device_mode").value,
		':InternetGatewayDevice.X_TWSZ-COM_Radio.2.DeviceOperationMode'    : $("device_mode").value
	});
	 
	if($('device_mode').value == "WirelessRepeater"){
		if(Form.Radio('band_type') == '1'){
		  $F(':InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.1.Enable', "1");
		  $F(':InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.2.Enable', "0");
	    }else{
		  $F(':InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.1.Enable', "0");
		  $F(':InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.2.Enable', "1");
	    }
	}else{
		$F(':InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.1.Enable', "0");
		$F(':InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.2.Enable', "0");
	}

	$('uiPostForm').submit();
}
function showModeItem(){
	if($("device_mode").value == "InfrastructureAccessPoint"){
		$("repeater_band").style.display = "none";
	}else{
		$("repeater_band").style.display = "block";
	}
}
function dealWithError(){
	if (G_Error != 1){
		return false;
	}
	
	var arrayHint = [];

	dealErrorMsg(arrayHint, G_Error_Msg);
}

addListeners(uiOnload, dealWithError);
