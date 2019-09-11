%% Uruchomic tylko raz!!!!!!!!!!!!!!!!!!!!1111111111111oneoneoneone
% Zalaczenie drukarki, otworzenie portu
drukarka = serial('/dev/ttyUSB1')
drukarka.BaudRate = 115200
drukarka.Terminator = 'CR/LF'
fopen(drukarka)