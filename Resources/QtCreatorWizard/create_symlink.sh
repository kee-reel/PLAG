read -p 'This tool will create symlink to plugin wizard. Set absolute path to Qt directory: ' path
ln -sf $(pwd)/Plugin $path/Tools/QtCreator/share/qtcreator/templates/wizards
