window.addEventListener('DOMContentLoaded', () => {
    const boxs = Array.from(document.querySelectorAll('.box'));
    const playerDisplay = document.querySelector('.display-player');
    const restartButton = document.querySelector('#restart');
    const gameAnnouncer = document.querySelector('.announcer');

    let gameBoard = ['', '', '', '', '', '', '', '', ''];
    let currentPlayer = 'X';
    let gameActive = true;

    const PLAYER_X_WON = 'PLAYER_X_WON';
    const PLAYER_O_WON = 'PLAYER_O_WON';
    const TIE = 'TIE';

    const gameRule = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],
        [0, 4, 8],
        [2, 4, 6]
    ];

    function handleResultValidation() {
        let roundWon = false;
        for (let i = 0; i <= 7; i++) {
            const rule = gameRule[i];
            const a = gameBoard[rule[0]];
            const b = gameBoard[rule[1]];
            const c = gameBoard[rule[2]];
            if (a === '' || b === '' || c === '') {
                continue;
            }
            if (a === b && b === c) {
                roundWon = true;
                break;
            }
        }

    if (roundWon) {
            announce(currentPlayer === 'X' ? PLAYER_X_WON : PLAYER_O_WON);
            gameActive = false;
            fetch('/tictactoe', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                }
            });
            return;
        }

    if (!gameBoard.includes(''))
        announce(TIE);
    }

    function createWinTag(player){
        const span = document.createElement('span');
        span.innerText = player;
        span.classList.add("player"+player);
        return span;
    }

    const announce = (type) => {
        switch(type){
            case PLAYER_O_WON:
                gameAnnouncer.innerText = 'Player ';
                gameAnnouncer.appendChild(createWinTag('O'));
                gameAnnouncer.appendChild(document.createTextNode(' Won'));
                break;
            case PLAYER_X_WON:
                gameAnnouncer.innerText = 'Player ';
                gameAnnouncer.appendChild(createWinTag('X'));
                gameAnnouncer.appendChild(document.createTextNode(' Won'));
                break;
            case TIE:
                gameAnnouncer.innerText = 'Tie';
                break;
        }
        gameAnnouncer.classList.remove('hide');
    };

    const isValidAction = (tile) => {
        if (tile.innerText === 'X' || tile.innerText === 'O'){
            return false;
        }

        return true;
    };

    const updateBoard =  (index) => {
        gameBoard[index] = currentPlayer;
    }

    const changePlayer = () => {
        playerDisplay.classList.remove(`player${currentPlayer}`);
        currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
        playerDisplay.innerText = currentPlayer;
        playerDisplay.classList.add(`player${currentPlayer}`);
    }

    const userAction = (tile, index) => {
        if(isValidAction(tile) && gameActive) {
            tile.innerText = currentPlayer;
            tile.classList.add(`player${currentPlayer}`);
            updateBoard(index);
            handleResultValidation();
            changePlayer();
        }
    }
    
    const resetBoard = () => {
        gameBoard = ['', '', '', '', '', '', '', '', ''];
        gameActive = true;
        gameAnnouncer.classList.add('hide');

        if (currentPlayer === 'O') {
            changePlayer();
        }

        boxs.forEach(tile => {
            tile.innerText = '';
            tile.classList.remove('playerX');
            tile.classList.remove('playerO');
        });
    }

    boxs.forEach( (box, index) => {
        box.addEventListener('click', () => userAction(box, index));
    });

    restartButton.addEventListener('click', resetBoard);
});