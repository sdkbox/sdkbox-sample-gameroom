
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
		this._super();

		sdkbox.PluginGameroom.log('Sample Startup')

		this.createTestMenu();

		var quit = new cc.MenuItemLabel(new cc.LabelTTF('QUIT', 'sans', 16), function () {
			sdkbox.PluginGameroom.log('QUIT');
			sdkbox.PluginGameroom.destroy();
		});
		var menu = new cc.Menu(quit);
		var winsize = cc.winSize;
		var size = quit.getContentSize();
		menu.x = winsize.width - size.width / 2 - 16;
		menu.y = size.height / 2 + 16;
		this.addChild(menu);

        return true;
	},
	createTestMenu: function () {
		cc.MenuItemFont.setFontName('sans');
		cc.MenuItemFont.setFontSize(40);

		if (typeof sdkbox === 'undefined') {
			cc.log('sdkbox undefined');
			return true;
		}

		var self = this;
		var winsize = cc.winSize;
		var coinsLabel = cc.Label.createWithSystemFont('Hello Js', 'Arial', 16);
		coinsLabel.setColor(cc.color(255, 0, 0, 128));
		coinsLabel.setPosition(winsize.width / 2, 80);
		self.addChild(coinsLabel);
		self.coinsLabel = coinsLabel;
		var showText = function (msg) {
			sdkbox.PluginGameroom.log(msg);
			self.coinsLabel.setString(msg);
		}
		self.showText = showText;

		self.menu = new cc.Menu();
		self.menu.y = 20
		self.addChild(self.menu)

		var logo = new cc.Sprite('res/Logo.png');
		var logoSize = logo.getContentSize();
		logo.x = logoSize.width / 2;
		logo.y = winsize.height - logoSize.height / 2;
		this.addChild(logo);

		sdkbox.PluginGameroom.init('523164037733626');
		sdkbox.PluginGameroom.setListener({
			onLoginAccessTokenMsg: function (handle) {
				sdkbox.PluginGameroom.log('============');
				sdkbox.PluginGameroom.log('onLoginAccessTokenMsg');
				sdkbox.PluginGameroom.log(JSON.stringify(handle, null, 2));
				if (handle.isValidToken) {
					self.showText('login successful');
				}
				else {
					self.showText('login failed');
				}
			},
			onFeedShareMsg: function (handle) {
				sdkbox.PluginGameroom.log('============');
				sdkbox.PluginGameroom.log('onFeedShareMsg');
				sdkbox.PluginGameroom.log('shared post id = ' + handle.postID);
				
			},
			onPurchaseIAPMsg: function (handle) {
				sdkbox.PluginGameroom.log('============');
				sdkbox.PluginGameroom.log('onPurchaseIAPMsg');
				sdkbox.PluginGameroom.log('payment ID = '+ handle.paymentID);
				sdkbox.PluginGameroom.log('amount = ' + handle.amount);
				sdkbox.PluginGameroom.log('curency = ' + handle.currency);
				sdkbox.PluginGameroom.log('purchase time = ' + handle.purchaseTime);
				sdkbox.PluginGameroom.log('product ID = ' + handle.productID);
				sdkbox.PluginGameroom.log('purchase token = ' + handle.purchaseToken);
				sdkbox.PluginGameroom.log('quantity = ' + handle.quantity);
				sdkbox.PluginGameroom.log('request id = ' + handle.requestID);
				sdkbox.PluginGameroom.log('status = ' + handle.status);
				sdkbox.PluginGameroom.log('signed req = ' + handle.signedReq);
				sdkbox.PluginGameroom.log('error code = ' + handle.errorCode);
				sdkbox.PluginGameroom.log('error msg = ' + handle.errorMsg);
				
			}, 
			onPurchaseTrialware: function (handle) {
				sdkbox.PluginGameroom.log('============');
				sdkbox.PluginGameroom.log('onPurchaseTrialware');
				sdkbox.PluginGameroom.log('has license = ' + handle.hasLicense);
			}
		});

		var btnLogin = new cc.MenuItemFont('Login', function () {
			sdkbox.PluginGameroom.login();
		}, this);

		var btnIsLoggedIn = new cc.MenuItemFont('Check Login', function () {
			sdkbox.PluginGameroom.log('==============');
			sdkbox.PluginGameroom.log('is login: ' + sdkbox.PluginGameroom.isLoggedIn());
		}, this);

		var btnFeedShare = new cc.MenuItemFont('Feed Share', function () {
			sdkbox.PluginGameroom.log('==============');
			sdkbox.PluginGameroom.log('feed share');
			sdkbox.PluginGameroom.feedShare(
				'',
				'https://www.facebook.com',
				'Testing Link Name',
				'Testing Link Caption',
				'Testing Link Description',
				'http://www.pamperedpetz.net/wp-content/uploads/2015/09/Puppy1.jpg',
				''
			);
		}, this);

		var btnIAP = new cc.MenuItemFont('Gameroom IAP', function () {
			sdkbox.PluginGameroom.log('==============')
			sdkbox.PluginGameroom.log('Gameroom IAP');
			sdkbox.PluginGameroom.purchaseIAP(
				'coins200',
				1,
				1,
				1,
				'',
				'',
				''
			);
		}, this);

		var btnIAPWithURL = new cc.MenuItemFont('Gameroom IAP with URL', function () {
			sdkbox.PluginGameroom.log('==============');
			sdkbox.PluginGameroom.log('Gameroom IAP with URL');
			sdkbox.PluginGameroom.purchaseIAPWithProductURL(
				'https://friendsmash-unity.herokuapp.com/payments/100coins.php',
				1,
				1,
				1,
				'',
				'',
				''
			);
		}, this);

		var btnPurchaseLicense = new cc.MenuItemFont('Gameroom Purchase License or Premium', function () {
			sdkbox.PluginGameroom.log('==============');
			sdkbox.PluginGameroom.log('Gameroom Purchase License or Premium');
			sdkbox.PluginGameroom.payPremium();
		});

		var btnCheckLicense = new cc.MenuItemFont('Gameroom Check License', function () {
			sdkbox.PluginGameroom.log('==============');
			sdkbox.PluginGameroom.log('Check License');
			sdkbox.PluginGameroom.hasLicense();
		});

		var menu = new cc.Menu(btnLogin, btnIsLoggedIn, btnFeedShare, btnIAP, btnIAPWithURL, btnPurchaseLicense, btnCheckLicense);
		menu.x = winsize.width / 2;
		menu.y = winsize.height / 2;
		menu.alignItemsVerticallyWithPadding(20);
		this.addChild(menu);
	}
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

