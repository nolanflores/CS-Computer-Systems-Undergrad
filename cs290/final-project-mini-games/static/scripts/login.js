const form = document.getElementById('playButton').addEventListener('click', function() {
    const username = document.getElementById('username').value.trim();
    if(username){
        fetch('/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({username}),
        }).then((response) => {
            if(response.redirected){
                window.location.href = response.url;
            }sole.log("== Response was not a redirect");
        }).catch((error) => {
            console.error("Error:", error);
        });
    }
});