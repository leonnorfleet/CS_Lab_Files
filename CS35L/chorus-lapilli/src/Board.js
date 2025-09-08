import './App.css';
import { useState } from 'react';

function Board() {
    const [turnX, setTurn] = useState(true); // keep track of turns
    const [tiles, setTiles] = useState(Array(9).fill(null)); // keep track of the values in each tile
    const [count, setCount] = useState(0); // count the number of turns
    const [msg, setMsg] = useState('X'); // change UI so players know whose turn it is
    const [remove, setRemove] = useState(false); // keep track of if a player has removed a piece
    const [lastPlacement, setPlacement] = useState(-1); // keep track of the position of the last removed piece so no one cheats
    var winner = (calculateWinner(tiles) ? true : false);

    return (
        <>
            <div className='game'>
                <div className='game-board'>
                    <p className='turn-text'>{winner ? 'Winner: ' : 'Next Player: '} 
                        {winner ? calculateWinner(tiles) : msg}</p>
                    <div className='row'>
                        <Tile value={tiles[0]} onTileClick={() => handleClick(0)}></Tile>
                        <Tile value={tiles[1]} onTileClick={() => handleClick(1)}></Tile>
                        <Tile value={tiles[2]} onTileClick={() => handleClick(2)}></Tile>
                    </div>
                    <div className='row'>
                        <Tile value={tiles[3]} onTileClick={() => handleClick(3)}></Tile>
                        <Tile value={tiles[4]} onTileClick={() => handleClick(4)}></Tile>
                        <Tile value={tiles[5]} onTileClick={() => handleClick(5)}></Tile>
                    </div>
                    <div className='row'>
                        <Tile value={tiles[6]} onTileClick={() => handleClick(6)}></Tile>
                        <Tile value={tiles[7]} onTileClick={() => handleClick(7)}></Tile>
                        <Tile value={tiles[8]} onTileClick={() => handleClick(8)}></Tile>
                    </div>
                    <p className='turn-text'>{(remove && !winner) ? '(Remove a Piece)' : '(Place a Piece)'}</p>
                </div>
            
                <div className="game-info">
                <button onClick={() => clearGame()}>Restart Game/Clear Board</button>
                <p className='turn'>Turn: {count}</p>
                </div>
            </div>
          </>
    );

    function handleClick(i) {
        const nextTile = tiles.slice();

        if ((nextTile[i] && !remove) || calculateWinner(tiles) || (i === lastPlacement)) {
            return;
        }

        if (!remove) {

            if (turnX) {
                nextTile[i] = 'X';
                setMsg('O')
            }
            else {
                nextTile[i] = 'O';
                setMsg('X')
            }
            setTurn(!turnX);
            setCount(count + 1);
            setPlacement(-1);

            if (count >= 5) {
                setRemove(!remove);
            }
        }
        else {
            if (turnX) {
                if (nextTile[i] === 'X') {
                    nextTile[i] = null;
                    setRemove(!remove);
                }
            }
            else {
                if (nextTile[i] === 'O') {
                    nextTile[i] = null;
                    setRemove(!remove);
                }
            }
            setPlacement(i);
        }
        setTiles(nextTile);
    }

    function clearGame() {
        setTurn(true);
        setTiles(Array(9).fill(null));
        setCount(0);
        setMsg('X');
        setRemove(false);
        setPlacement(-1);
        winner = (calculateWinner(tiles) ? true : false);
    }

}

function Tile({value, onTileClick}) {
    return (
      <button className='tile' onClick={onTileClick}>
        {value}
      </button>
    );
}

function calculateWinner(tiles) {
    const lines = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],
        [0, 4, 8],
        [2, 4, 6]
      ];
      for (let i = 0; i < lines.length; i++) {
        const [a, b, c] = lines[i];
        if (tiles[a] && tiles[a] === tiles[b] && tiles[a] === tiles[c]) {
          return tiles[a];
        }
      }
      return null;
}

export default Board;