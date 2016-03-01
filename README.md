# Snake

## Installation
###Dépendances du projet
`bash install.sh`   
Ceci installera toutes les dépendances du projet.
###Librairies cmocka`
`cd ~/Downloads`               
`xz -d cmocka-1.0.1.tar.xz`                                 
`tar vxf cmocka-1.0.1.tar`               
`cd cmocka-1.0.1`                 
`mkdir build`                       
`cd build`                        
`cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..`        
`make`                
`sudo make install`                   
## Memo Git

* **Clone**: récupérer le repo  
`git clone https://github.com/MrYawe/snake.git`

* **Commit**: sauvegarder les modifications en local     
`git add -A`
`git commit -am "mon message de commit"`

* **Push**: envoi des modifications à tout le monde      
N'oubliez pas de toujours sauvegarder en local avant de push.    
`git push`

* **Pull**: récuperer les modifications des autres      
N'oubliez pas de toujours sauvegarder en local avant de pull.   
`git pull`

* **--assume-unchanged**: ne pas tenir compte des changements en local d'un fichier       
Utilisé pour le main.c lors du développement des classes sans avoir à commit le fichier main de test        
`git update-index --assume-unchanged <filename>`
* **--no-assume-unchanged**: arrêter d'ignorer les changements du fichier       
`git update-index --no-assume-unchanged <filename>`

## Liens
* [Cahier des charges](https://goo.gl/QdoBUI)
* [Trello](https://trello.com/b/cI9Wid56/ipi-snake)
* [Slack](https://larakis.slack.com)
* [Cmocka tutorial](http://zhuyong.me/blog/2014/03/19/c-code-unit-testing-using-cmocka/)
