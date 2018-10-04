namespace iwdg {
    
    class Driver: public genericTimer::Timer {

    public:

        void init() {
            target::RCC.CSR.setLSION(1);
            target::IWDG.KR = 0x00005555;
            target::IWDG.PR.setPR(4);
            target::IWDG.KR = 0x0000CCCC;
            target::IWDG.KR = 0x0000AAAA;
            target::GPIOB.MODER.setMODER(4, 1);
            start(100);
        }

        void onTimer() {            
            target::IWDG.KR = 0x0000AAAA;
            target::GPIOB.ODR.setODR(4, ~target::GPIOB.IDR.getIDR(4));
    		start(100);
	    }

        void reboot() {
            target::IWDG.KR = 0x00005555;
            target::IWDG.RLR.setRL(0);
        }

    };
}