const originalList = [];
const rows = document.getElementsByTagName("tr");
for(let i = 1; i < rows.length; i++){
    originalList.push(rows[i]);
}

const UP = "▲", DOWN = "▼";

let arrow = null;
console.log(arrow);
let selectedSort = null;
let sortDirection = null;

const headers = document.getElementsByTagName("th");
for(let i = 0; i < headers.length; i++){
    headers[i].addEventListener("click", function(){
        if(selectedSort !== i){
            if(arrow){
                arrow.remove();
                arrow = null;
            }
            selectedSort = i;
            sortDirection = DOWN;
            arrow = document.createElement("span");
            arrow.classList.add("arrow");
            arrow.textContent = DOWN;
            headers[i].appendChild(arrow);
        }else{
            if(sortDirection === DOWN){
                sortDirection = UP;
                arrow.textContent = UP;
            }else{
                selectedSort = null;
                sortDirection = null;
                arrow.remove();
                arrow = null;
            }
        }
        sortData();
    });
}

function sortData(){
    let list = [];
    if(selectedSort === null){
        list = originalList;
    }else{
        for(let i = 0; i < originalList.length; i++){
            list.push(originalList[i]);
        }
        if(selectedSort === 0){
            list.sort(function(a, b){
                if(sortDirection === DOWN){
                    return a.children[0].textContent.localeCompare(b.children[0].textContent);
                }else{
                    return b.children[0].textContent.localeCompare(a.children[0].textContent);
                }
            });
        }else{
            list.sort(function(a, b){
                if(sortDirection === UP){
                    return parseInt(a.children[selectedSort].textContent) - parseInt(b.children[selectedSort].textContent);
                }else{
                    return parseInt(b.children[selectedSort].textContent) - parseInt(a.children[selectedSort].textContent);
                }
            });
        }
    }
    for(let i = 0; i < list.length; i++){
        list[i].parentNode.appendChild(list[i]);
    }
}