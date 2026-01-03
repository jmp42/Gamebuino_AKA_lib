

2025/12/26
	! Nettoyage lib, réarrangement en composant ESP-IDF :
		drivers bas niveau dans le dossier gb_ll (a priori pas utilisé directement)
		librairies utilisateur dans le dossier gb_lib
	+ ajout gb_audio_track_wav : lecture depuis WAV sur sdcard, WAV en mémoiure ESP, ou raw en mémoire de l'ESP
		NOTE : #include "assets/WAV_SYSTEM.h" => embedded Gamebuino system sound : gb_wav_system_xxx
			eg : track_wav.play_wav( gb_wav_system_explode );
	+ ajout gb_audio_track_tone : génération d'un sine avec freq debut/fin et volume début/fin, et durée
	+ ajout gb_audio_track_fx : chainage de notes avecs volume/pitch sur base gb_audio_track_tone chainés 
	+ ajout gb_core : lecture touches, joystock, power off, tools divers
	+ ajout gb_audio_track_pmf : player de pmf : cf https://github.com/jeancharleslebeau-gif/pAKAman 
								pmf https://github.com/JarkkoPFC/arduino-music-player
								base de sons : modarchive.org
								tracker : https://milkytracker.org/
		sound MCU usage at :		22k		44k						
		track_wav(rom)				0.2%	0.4%
		track_fx/track_tone			0.25%	0.5%
		track_pmf(pacman.mod)		0.7%	1.5%		
		track_wav(sdcard)			6%		9%

								
TODO first !
	Bruit de fond casque et scintillement écran
	test mul div uint32 float32

#TODO list

	audio	
		TBD : ajouter option pour rendu son sur 2nd coeur ( réduction latence/taille des buffers )
		TBD : Ajouter support bruitages avec gb_audio_track_pmf et banque système.
		TBD : Ajouter support pitch sur gb_audio_track_wav

	graphics
		components/gamebuino/include/LCD.h : macro RGB565(R,G,B)
		Ajouter mesure FPS
		implémenter mode indexé
		Option primari sram/psram
		Option secondary sram/psram/none
		Option video 8/16
		Option vsync ON/OFF
		ajouter classe sprite avec gestion collision et phisique
		ajouter classe tuilemap
		ajouter classe raycasting
		ajouter classe 3d matrices
		ajouter classe menu HUD ( options de jeux, ...)

	system	
		ajouter init des dépendances, avec gestion appels multiples       
		ajouter mass storage
		ajouter gestionnaire de message d'erreur, type log_add(versbose, warning, error) avec popup sur LCD et log fichier
		ajouter menu system sur touche RUN ( pause, menu ). La touche MENU devient libre pour utilisateur
		ajouter classe API copnnectivité ( jeu en lignes, installation depuis serveru... )
		ajouter capture image et flux vidéo
		Tools pour concaténer des ressources (bmp, pmf, wav) en fichier ".rc". 
			Le tool génère un enum à utiliser dans les objets play_wav, draw_sprite, play_pmf ... à partir d'acronymes utilisateur
			Eg : SON1, PICTO1, PICTO2, PMF1, PMF2, PMFZIK...


	touches	
		ajouter détection press, release, hold(ms)

	tutoriels
		Création de contenus
		Documenter l'API python et C++ :
			Tutoriel introduction à la programmation
			Langage C/C++ motc clefs
			Langage C/C++ types de variables
			Langage C/C++ boucles
			Langage C/C++ conditions
			Langage C/C++ arithmétique et logique
			Langage C/C++ algorithmique
			Langage C/C++ notions objet - introduction au C++
			Langage C/C++ notions objet - modèle objet de jeux 2d ( collection d'objets avec propriétés et méthodes )
			etude de cas : stratégie de rendu : recompposer l'ecran complet vs mettre a jour le contenu
			etude de cas : scrool vertical ( type star chip invaders )
			etude de cas : pong
			etude de cas : pacman
			etude de cas : tétris
			etude de cas : casse brique
			etude de cas : fausses perspectives(outrun)
			etude de cas : ray casting
			etude de cas : mode 7 ( cfr super ness star wars )
			etude de cas : pinball
			Tuto : créer un skin si maintenu ( cuir, … )
			etude de cas : compositeur de musique type fasttracker / jeu de rithme (pmf)
			tuto C/C++  : synthède de son FM ( vintage 8bits )
			tuto C/C++  : synthède de son WAV (mélangeurs)
			tuto C/C++  : rendu 3D - les bases
			tuto C/C++  : rendu 3D - sommets
			tuto C/C++  : rendu 3D - polyngomes 
			tuto C/C++  : rendu 3D - textures
			tuto C/C++  : rendu 3D - ombrage de Goureau
			tuto C/C++  : modéliser en 3D : Fusion, blender ou autre…


