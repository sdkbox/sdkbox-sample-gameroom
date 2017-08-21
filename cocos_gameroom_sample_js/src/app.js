
var HelloWorldLayer = cc.Layer.extend({
	sprite: null,
	app_id: '313416692430467',
	test_app_id: '523164037733626',
    ctor:function () {
		this._super();

		this.createTestMenu();
		cc.log('Sample Startup')

		var quit = new cc.MenuItemLabel(new cc.LabelTTF('QUIT', 'sans', 24), function () {
			cc.log('QUIT');
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
		var coinsLabel = cc.Label.createWithSystemFont('Hello Js', 'Arial', 24);
		coinsLabel.setColor(cc.color(255, 0, 0, 128));
		coinsLabel.setPosition(winsize.width / 2, 80);
		self.addChild(coinsLabel);
		self.coinsLabel = coinsLabel;
		var showText = function (msg) {
			cc.log(msg);
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

		sdkbox.PluginGameroom.init(this.app_id);
		sdkbox.PluginGameroom.setListener({
			onLoginAccessTokenMsg: function (handle) {
				cc.log('============');
				cc.log('onLoginAccessTokenMsg');
				cc.log(JSON.stringify(handle, null, 2));
				if (handle.isValidToken) {
					self.showText('login successful');
				}
				else {
					self.showText('login failed');
				}
			},
			onFeedShareMsg: function (handle) {
				cc.log('============');
				cc.log('onFeedShareMsg');
				self.showText('onFeedShareMsg');
				cc.log('shared post id = ' + handle.postID);
				
			},
			onPurchaseIAPMsg: function (handle) {
				cc.log('============');
				cc.log('onPurchaseIAPMsg');
				self.showText('onPurchaseIAPMsg');
				cc.log('payment ID = '+ handle.paymentID);
				cc.log('amount = ' + handle.amount);
				cc.log('curency = ' + handle.currency);
				cc.log('purchase time = ' + handle.purchaseTime);
				cc.log('product ID = ' + handle.productID);
				cc.log('purchase token = ' + handle.purchaseToken);
				cc.log('quantity = ' + handle.quantity);
				cc.log('request id = ' + handle.requestID);
				cc.log('status = ' + handle.status);
				cc.log('signed req = ' + handle.signedReq);
				cc.log('error code = ' + handle.errorCode);
				cc.log('error msg = ' + handle.errorMsg);
				
			}, 
			onHasLicenseMsg: function (handle) {
				cc.log('============');
				cc.log('onHasLicenseMsg');
				self.showText('onHasLicenseMsg');
				cc.log('has license = ' + handle.hasLicense);
			},
			onAppRequestMsg: function (handle) {
				cc.log('============');
				cc.log('onAppRequestMsg');
				self.showText('onAppRequestMsg');
				cc.log('objectID = ' + handle.objectiD);
				cc.log('to user: ' + handle.toUser);
			}
		});

		cc.MenuItemFont.setFontSize(24);
		var btnLogin = new cc.MenuItemFont('Gameroom Login', function () {
			sdkbox.PluginGameroom.login();
		}, this);

		var btnLoginWithScopes = new cc.MenuItemFont('Gameroom Login With Scopes', function () {
			sdkbox.PluginGameroom.loginWithScopes(2, ['public_profile', 'email']);
		}, this);


		var btnIsLoggedIn = new cc.MenuItemFont('Gameroom Check Login', function () {
			cc.log('==============');
			cc.log('Gameroom Check login: ' + sdkbox.PluginGameroom.isLoggedIn());
		}, this);

		var btnFeedShare = new cc.MenuItemFont('Gameroom Feed Share', function () {
			cc.log('==============');
			cc.log('Gameroom Feed Share');
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
			cc.log('==============')
			cc.log('Gameroom IAP');
			sdkbox.PluginGameroom.purchaseIAP(
				'sdkbox_product_1',
				1,
				1,
				1,
				'',
				'',
				''
			);
		}, this);

		var btnIAPWithURL = new cc.MenuItemFont('Gameroom IAP with URL', function () {
			cc.log('==============');
			cc.log('Gameroom IAP with URL');
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
			cc.log('==============');
			cc.log('Gameroom Purchase License or Premium');
			sdkbox.PluginGameroom.payPremium();
		});

		var btnCheckLicense = new cc.MenuItemFont('Gameroom Check License', function () {
			cc.log('==============');
			cc.log('Gameroom Check License');
			sdkbox.PluginGameroom.hasLicense();
		});

		var btnActivateApp = new cc.MenuItemFont('Gameroom Activate App', function () {
			cc.log('==============');
			cc.log('Gameroom Activate App');
			sdkbox.PluginGameroom.activateApp();
		});

		var btnAppEvent = new cc.MenuItemFont('Gameroom Send App Event', function () {
			cc.log('==============');
			cc.log('Gameroom Send App Event');
			sdkbox.PluginGameroom.logAppEvent('test_event_1', { 'key1': 'val1', 'key2': 'val2' });
			sdkbox.PluginGameroom.logAppEventWithValueToSum('test_event_2', { 'key3': 'val3', 'key4': 'val4' }, 10.24);
		});

		var btnAppRequest = new cc.MenuItemFont('Gameroom Send App Request', function () {
			cc.log('==============');
			cc.log('Gameroom Send App Request');
			sdkbox.PluginGameroom.appRequest('hello', '', '', '1506344439429504', '', '', '', '', '');
		});

		var menu = new cc.Menu(btnLogin, btnLoginWithScopes, btnIsLoggedIn, btnFeedShare, btnIAP, btnIAPWithURL, btnPurchaseLicense, btnCheckLicense, btnActivateApp, btnAppEvent, btnAppRequest);
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

