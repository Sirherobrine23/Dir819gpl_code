var G_SysToken_ajax  = "<?echo $var:sys_Token?>";
var G_ApUpScan = [];
var n = 0, G_AplistUpdate=0, idx = 0;
<?objget :InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration. "Enable ApCliScanState"
`	G_ApUpScan[n] = [];
    G_ApUpScan[n][0] = ":InternetGatewayDevice.LANDevice.1.X_TWSZ-COM_ApCliConfiguration.$00.";
	G_ApUpScan[n][1] = "$01";
	G_ApUpScan[n][2] = "$02";
	n++;
`?>

for(var i=0; i<G_ApUpScan.length; i++){
	
	if(G_ApUpScan[i][1] == "1")
	{
		if(G_ApUpScan[i][2] == "0"){
			G_AplistUpdate = 0;
			break;
		}else if(G_ApUpScan[i][2] == "2"){
			G_AplistUpdate = 2;	
			break;
		}else if(G_ApUpScan[i][2] == "1"){
			G_AplistUpdate = 1;
			break;
		}
	}
	
}