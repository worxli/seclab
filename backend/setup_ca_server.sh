echo 'install system software'
sudo apt install python3-pip
sudo apt-get install python-pip python-dev build-essential
sudo pip install virtualenv virtualenvwrapper
sudo pip install --upgrade pip
sudo apt-get install python3-dev
sudo apt-get install libmysqlclient-dev
sudo apt-get install nginx


echo 'creating virtualenv'
cp ~/.bashrc ~/.bashrc-org
printf '\n%s\n%s\n%s' '# virtualenv' 'export WORKON_HOME=~/virtualenvs' \
'source /usr/local/bin/virtualenvwrapper.sh' >> ~/.bashrc
source ~/.bashrc
mkdir -p $WORKON_HOME
mkvirtualenv --python=python3 seclab


echo 'get repo and install requirements'
sudo apt-get install git
mkdir caServer && cd caServer
git init
git remote add -f origin https://github.com/worxli/seclab.git
git config core.sparseCheckout true
echo "backend/" >> .git/info/sparse-checkout
git pull origin master
cd backend/djangoBackend
pip install -r requirements.txt


echo 'installing mysql'
sudo apt-get update
sudo apt-get install mysql-server
sudo mysql_secure_installation
sudo mysql_install_db
#CREATE DATABASE imovies;
#GRANT ALL PRIVILEGES ON dbTest.* To 'user'@'hostname' IDENTIFIED BY 'password';


echo 'configuring uwsgi'
sudo mkdir /var/log/uwsgi
sudo chown cadmin /var/log/uwsgi
sudo mkdir /var/run/uwsgi
sudo chown /var/run/uwsgi
cd ../uwsgiConf
sudo cp uwsgi.conf /etc/init/
sudo cp caserver.ini /etc/uwsgi/sites/

echo 'configuring nginx'
cd ../nginxConfigs/
sudo cp uwsgi_params /etc/nginx/conf.d/
sudo cp seclab-webserver /etc/nginx/sites-available/
cd /etc/nginx/sites-enabled
sudo ln -s /etc/nginx/sites-available/seclab-webserver
sudo rm default
sudo mkdir /etc/nginx/certs




