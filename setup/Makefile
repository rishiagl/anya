null :
	echo "Please provide any one of the command:- install or postgres"

.phony : env-setup extras database install postgres

env-setup :
	sudo apt install git -y;
	sudo apt install gcc -y;
	sudo apt install g++ -y;
	sudo apt install cmake -y;

extras : 
	sudo apt install libboost-all-dev;
	sudo apt install libjsoncpp-dev;
	sudo apt install uuid-dev;
	sudo apt install openssl;
	sudo apt install libssl-dev;
	sudo apt install zlib1g-dev;

database:
	sudo apt-get install libsqlite3-dev;
	sudo apt-get install libhiredis-dev;

postgres:
	sudo apt-get -y install lsb-release gnupg;\
	sudo sh -c 'echo "deb http://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list';\
	wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add - ;\
	sudo apt-get update;\
	sudo apt-get -y install postgresql libpq-dev postgresql-server-dev-all; \
	sudo apt update;


install: env-setup extras
	cd /usr/local;\
	sudo git clone https://github.com/drogonframework/drogon;\
	cd drogon;\
	sudo git clone https://github.com/an-tao/trantor.git; \
	sudo git submodule update --init;\
	sudo mkdir build;\
	cd build;\
	sudo cmake ..;\
	sudo make && sudo make install;