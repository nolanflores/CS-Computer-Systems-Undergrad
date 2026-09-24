document.addEventListener('DOMContentLoaded', () =>{
    const cards = document.querySelectorAll('.memory-card');
    let hasFlippedCard = false;
    let lockBoard = false;
    let firstCard, secondCard;
    let matchedPairs = 0;
    const totalPairs = cards.length / 2
    const congratsMessageDiv = document.getElementById('congrats-message');

    
    function flipCard(){
        if (lockBoard) return;
        
        if (this === firstCard) return;
        this.classList.add('flip');
        
        if (!hasFlippedCard){
        hasFlippedCard = true;
        firstCard = this;
        return;
        }
        secondCard = this;
        checkForMatch();
    }
    
    function checkForMatch(){
        let isMatch = firstCard.dataset.framework === secondCard.dataset.framework;
        isMatch ? disableCards() : unflipCards();
        if (isMatch){
        matchedPairs++; 
        if (matchedPairs === totalPairs){ 
        congratsMessageDiv.style.display = 'block'; 
        while (congratsMessageDiv.firstChild) {
        congratsMessageDiv.removeChild(congratsMessageDiv.firstChild);
                }
        const congratsText = document.createTextNode("Congratulations! You've matched all pairs!");
        congratsMessageDiv.appendChild(congratsText);
        fetch('/cards', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            }
        });
            }
        }
    }

    function disableCards(){
        firstCard.removeEventListener('click', flipCard);
        secondCard.removeEventListener('click', flipCard);
        resetBoard();
    }
    
    function unflipCards(){
        lockBoard = true;
        setTimeout(() =>{
        firstCard.classList.remove('flip');
        secondCard.classList.remove('flip');
        resetBoard();
        }, 1500);
    }
    
    function resetBoard(){
        [hasFlippedCard, lockBoard] = [false, false];
        [firstCard, secondCard] = [null, null];
    }
    
    function shuffleCards(){
        cards.forEach(card =>{
        let randomPos = Math.floor(Math.random() * totalPairs * 2);
        card.style.order = randomPos;
        });
    }
    
    (function initializeGame(){
        shuffleCards();
        cards.forEach(card => card.addEventListener('click', flipCard));
    })();
        document.getElementById('reset-button').addEventListener('click', () =>{
        cards.forEach(card => card.classList.remove('flip'));
        matchedPairs = 0; 
        shuffleCards();
        resetBoard();
        congratsMessageDiv.style.display = 'none';
    });
});