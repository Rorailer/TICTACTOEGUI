#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"Button/Button.hpp"

using namespace std;


//! Check if mouse is over a button.
bool isMouseOverText(const sf::Text &text, const sf::RenderWindow &window) {
    sf::FloatRect bounds = text.getGlobalBounds();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}



//! Pause Overlay
void overlay(sf::RenderWindow& window, sf::Font &font){
    
   


    sf::RectangleShape pause_overlay(sf::Vector2f(700,500));
    pause_overlay.setFillColor(sf::Color(225,225,225,225));
    pause_overlay.setPosition(50,50);

    window.draw(pause_overlay);

    }

//! Pause menu
void pauseMenu(sf::RenderWindow& window,sf::Font& font , int p1Wins , int p2Wins,int pDraws, bool& isPaused, int& game_mode){
    string score_string;
    if(game_mode == 1){
        
        score_string = "Player Wins: " + to_string(p1Wins) + "\tComputer Wins: " + to_string(p2Wins) +"\n\t\t\t\t\t Draws: " + to_string(pDraws);
    }
    else if(game_mode == 2){
        
        score_string = "Player 1 Wins: " + to_string(p1Wins) + "\tPlayer 2 Wins: " + to_string(p2Wins) +"\n\t\t\t\t\t Draws: " + to_string(pDraws);
    }
    
    //Text
    sf::Text Paused;
    Paused.setFont(font);
    Paused.setString("Game Paused");
    Paused.setStyle(sf::Text::Bold);
    Paused.setPosition((window.getSize().x/2) - (Paused.getGlobalBounds().width/2),window.getSize().y*0.25);

    //Quit Button
    sf::Text Quit;
    Quit.setString("Quit!");
    Quit.setFont(font);
    Quit.setFillColor(sf::Color::Black);
    Quit.setStyle(sf::Text::Italic);
    Quit.setStyle(sf::Text::Underlined);
    Quit.setPosition(((window.getSize().x/6)*5)-(Quit.getGlobalBounds().width/2),window.getSize().y*0.6667);


    sf::Text Resume;
    Resume.setString("Resume!");
    Resume.setFont(font);
    Resume.setFillColor(sf::Color::Black);
    Resume.setStyle(sf::Text::Italic);
    Resume.setStyle(sf::Text::Underlined);
    Resume.setPosition((window.getSize().x/6)-(Resume.getGlobalBounds().width/2),window.getSize().y*0.6667);


    // Main Menu Button
    sf::Text main_menu;
    main_menu.setString("Main Menu");
    main_menu.setFont(font);
    main_menu.setFillColor(sf::Color::Black);
    // main_menu.setStyle(sf::Text::Italic);
    main_menu.setStyle(sf::Text::Underlined);
    main_menu.setPosition(((window.getSize().x/6)*3)-(main_menu.getGlobalBounds().width/2),window.getSize().y*0.6667);

    sf::Text Score;
    Score.setFont(font);
    Score.setFillColor(sf::Color::Black);
    
    Score.setString(score_string);
    Score.setCharacterSize(30);

    Score.setStyle(sf::Text::Italic);
    // Score.setStyle(sf::Text::Underlined);x
    Score.setPosition((window.getSize().x/2)-(Score.getGlobalBounds().width/2),(window.getSize().y*0.4585)-(Score.getGlobalBounds().height/2));
    

    //clear
    window.clear(sf::Color::Black);

    //Draw
    overlay(window,font);

    window.draw(Paused);
    window.draw(Score);
    window.draw(Quit);
    window.draw(main_menu);
    window.draw(Resume);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverText(Quit, window)) {
        window.close();
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverText(Resume, window)){
        
        //^ Fix a bug, when resume was pressed the cell below resume was selected as well, This clears all pending inputs
        sf::Event event;
        while (window.pollEvent(event)) {
            break;
        }
        //^</Fix>

        isPaused = false;
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverText(main_menu,window)){
        game_mode = 0;
        isPaused = false;
    }


}








//! Text to put over overlay if someone won or draw
void win(sf::RenderWindow& window,sf::Font& font, string whoWon , int playerWins , int compWins){

    //Text
    sf::Text winner;
    winner.setFont(font);
    winner.setString(whoWon + "Won!!");
    winner.setStyle(sf::Text::Bold);
    winner.setPosition((window.getSize().x/2) - (winner.getGlobalBounds().width/2),window.getSize().y*0.25);

    //Stats
    sf::Text stats;
    stats.setFont(font);
    stats.setString("Player 1 Wins: " + to_string(playerWins) + "\nPlayer 2 Wins: " + to_string(compWins));
    stats.setPosition((window.getSize().x/2)-(stats.getLocalBounds().width/2),window.getSize().y/2);
   
   
   
   
   
   
    //Button
    sf::Text Quit;
    Quit.setString("Quit!");
    Quit.setFont(font);
    Quit.setFillColor(sf::Color::Black);
    Quit.setStyle(sf::Text::Italic);
    Quit.setStyle(sf::Text::Underlined);
    Quit.setPosition(window.getSize().x/3,window.getSize().y*0.66);



    sf::Text Continue;
    Continue.setString("Continue!");
    Continue.setFont(font);
    Continue.setFillColor(sf::Color::Black);
    Continue.setStyle(sf::Text::Italic);
    Continue.setStyle(sf::Text::Underlined);
    Continue.setPosition((window.getSize().x/3)*2,window.getSize().y*0.66);


    //Draw
    overlay(window,font);

    window.draw(winner);
    window.draw(Quit);
    window.draw(Continue);
    window.draw(stats);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverText(Quit, window)) {
        window.close();
    }
    else if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverText(Continue,window)){
        
    }

}





//! Vector AI
void VAI(vector<int>& cells , int& Random, vector<string>& buttonstate){
    srand(time(0));
    while(buttonstate[Random] != ""){

        int Index = rand() % cells.size();
        Random = cells[Index];
    }
    
    
        if (!cells.empty()) {

            cells.erase(remove(cells.begin(),cells.end(), Random), cells.end());

            buttonstate[Random] = "O";

            }
        else{}
}


//! Checking Winning
bool winchecklogic(vector<string>& buttonState, char symbol) {
    // Convert symbol to a string for comparison
    string symbolStr(1, symbol);

    // rows
    if ((buttonState[0] == symbolStr && buttonState[1] == symbolStr && buttonState[2] == symbolStr) ||
        (buttonState[3] == symbolStr && buttonState[4] == symbolStr && buttonState[5] == symbolStr) ||
        (buttonState[6] == symbolStr && buttonState[7] == symbolStr && buttonState[8] == symbolStr)) {
        return true;
    }

    // columns
    if ((buttonState[0] == symbolStr && buttonState[3] == symbolStr && buttonState[6] == symbolStr) ||
        (buttonState[1] == symbolStr && buttonState[4] == symbolStr && buttonState[7] == symbolStr) ||
        (buttonState[2] == symbolStr && buttonState[5] == symbolStr && buttonState[8] == symbolStr)) {
        return true;
    }

    // diagonals
    if ((buttonState[0] == symbolStr && buttonState[4] == symbolStr && buttonState[8] == symbolStr) ||
        (buttonState[2] == symbolStr && buttonState[4] == symbolStr && buttonState[6] == symbolStr)) {
        return true;
    }

    return false;
}


//! Logic to find who won.    Returns Who won
string who_Won(bool result, char symbol, int& draws, int& compWins, int& playerWins, int& compLoss, int& playerLoss){ // Resturns who won.
    if(result){
        if(symbol == 'X'){
            playerWins++;
            compLoss++;
            return "Player";
        }else{
            compWins++;
            playerLoss++;
            return "Computer";
        }
    }else{return "";}

}

//! Storing Score
void store_score(int p1Wins, int p2Wins , int PDraws , int PWins ,int CWins , int CDraws){
        ofstream scoreFile("score.txt");
        if(!scoreFile){
            cerr << "Error Opeing File" << endl;
        }
        else if(scoreFile){
            scoreFile << p1Wins << endl;
            scoreFile << p2Wins << endl;            
            scoreFile << PDraws << endl;
            scoreFile << PWins << endl;
            scoreFile << CWins << endl;
            scoreFile << CDraws << endl;
            scoreFile.close();

        }
}

//! Read Score
void read_score(int& p1Wins, int& p2Wins , int& PDraws , int& PWins ,int& CWins , int& CDraws){
    ifstream scoreFile("score.txt");

    if(!scoreFile){
        cerr << "Error Opeing File";
    }
    else if (scoreFile){
        string linedata;
        for(int line = 0 ; line >6 ; line++){
            switch(line){
                case 0:
                    scoreFile >> linedata;
                    p1Wins = stoi(linedata);
                    break;
                case 1:
                    scoreFile >> linedata;
                    p2Wins = stoi(linedata);
                    break;
                case 2:
                    scoreFile >> linedata;
                    PDraws = stoi(linedata);
                    break;
                case 3:
                    scoreFile >> linedata;
                    PWins = stoi(linedata);
                    break;
                case 4:
                    scoreFile >> linedata;
                    CWins = stoi(linedata);
                    break;
                case 5:
                    scoreFile >> linedata;
                    CDraws = stoi(linedata);
                    break;
            }
            }
    }
}




int main(){
    
    
    
    
    
    //*Variables

    vector<string> buttonstate = {"", "", "", "", "", "", "", "", ""};
    
    string buttonState[9] = {"", "", "", "", "", "", "", "", ""};
    vector<int> cells = {0,1,2,3,4,5,6,7,8};
    
    string p1Symbol = "X";
    string p2Symbol = "O";
    string compSymbol = "O";

    float lineThickness = 3;
    
    int p1Wins = 0;
    int p2Wins = 0;
    int p1Loss = 0;
    int p2Loss = 0;
    int Cdraws = 0;
    int Pdraws = 0;
    int compWins = 0;
    int playerWins = 0;
    int compLoss = 0;
    int playerLoss = 0;

    //Colors
    int colour_lightgrey[4] = {211,211,211,100};
    int colour_dimWhite[4] = {224, 224, 224, 255};
    int colour_dimBlack[4] = {51, 51, 51, 255};
    int colour_invisible[4] = {211,211,211,2};
    int colour_DarkBlue[4] = {52, 45, 113,255};

    //kinda variables. Shapes for pause button.
    sf::RectangleShape rect1, rect2,rect3;
    // *</Variables>
    
    
    // *Main Window Creation
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Tac Toe", sf::Style::Titlebar);
    window.setSize(sf::Vector2u(800,600));
    //*</Main Window>


    //*Font
    sf::Font font;
    if (!font.loadFromFile("Helvetica-Bold.ttf")) {
        std::cout<< "Couldn't Load Font.";
    }
    //*</Font>
    
    
    //*Turn Text
    sf::Text playerTurn;
    playerTurn.setFont(font);
    playerTurn.setCharacterSize(15);
    playerTurn.setFillColor(sf::Color::White);
    playerTurn.setStyle(sf::Text::Bold);
    playerTurn.setStyle(sf::Text::Underlined);
    //*</Turn Text>

    
    
    
    
    
    
    
    //Loading Background Texture and setting vlaues
    
    /*
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Background.jpeg");
    if (!backgroundTexture.loadFromFile("Background.jpeg")) {
        std::cout<< "Couldn't load texture.";
    }

    sf::Sprite Background;
    Background.setTexture(backgroundTexture);
    Background.setScale(800,600);
    */
    // Background.setPosition(0,0);

    //</Background>
    
    




    //*Creating Board 
    
    //Vertical Line 1
    sf::RectangleShape Vline1(sf::Vector2f(lineThickness,420));
    Vline1.setPosition(306.67,90);
    Vline1.setFillColor(sf::Color::White);


    //Vertical Line 2
    sf::RectangleShape Vline2(sf::Vector2f(lineThickness,420));
    Vline2.setPosition(493.33,90);
    Vline2.setFillColor(sf::Color::White);

    //Horizontal line 1
    sf::RectangleShape Hline1(sf::Vector2f(560,lineThickness));
    Hline1.setPosition(120,230);
    Hline1.setFillColor(sf::Color::White);

    //Horizontal line 2
    sf::RectangleShape Hline2(sf::Vector2f(560,lineThickness));
    Hline2.setPosition(120,370);
    Hline2.setFillColor(sf::Color::White);

    //*</Building Board>





    


    



    
    
    //*Variables in game loop
    bool paused = true;    
    int turn = 0;
    int Game_mode = 0; // 0 is menu, 1 is pvp 2 is pvAI
    int compChoice;
    //*</Game loop variables>
    
    //! Game Loop
    
    //! Game Loop
    //! Game Loop
    
    //! Game Loop
    //! Game Loop
    while(window.isOpen()){
        
        string symbol;

       
        
        //*Creating Button and setting their positions.

        //Cell Buttons
        Button button00(buttonstate[0],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        Button button01(buttonstate[1],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        Button button02(buttonstate[2],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        Button button10(buttonstate[3],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        Button button11(buttonstate[4],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        Button button12(buttonstate[5],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        Button button20(buttonstate[6],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        Button button21(buttonstate[7],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        Button button22(buttonstate[8],font , 185.67 , 139, colour_invisible, colour_DarkBlue , 70);
        button00.setPosition(120,90);
        button01.setPosition(305.67,90);
        button02.setPosition(491.33,90);
        button10.setPosition(120,229);
        button11.setPosition(305.67,229);
        button12.setPosition(491.33,229);
        button20.setPosition(120,368);
        button21.setPosition(305.67,368);
        button22.setPosition(491.33,368);

        //Pause Button
        Button pause_button("",font,20,20,colour_invisible, colour_invisible, 0);
        pause_button.setPosition(1,1);

        //Menu PVP Button
        Button pvpButton("Player vs Player",font,(window.getSize().x/3)+30,window.getSize().y*0.1,colour_lightgrey, colour_dimBlack , 30);
        pvpButton.setPosition((window.getSize().x/2)-(pvpButton.getSize().x/2),window.getSize().y*0.3334);
        
        Button pvAIButton("Player vs Computer",font,(window.getSize().x/3)+30,window.getSize().y*0.1,colour_lightgrey, colour_dimBlack , 30);
        pvAIButton.setPosition((window.getSize().x/2)-(pvpButton.getSize().x/2),(window.getSize().y*0.3334)+(window.getSize().y*0.15));

        Button menuQuit("Quit",font,(window.getSize().x/3)+30,window.getSize().y*0.1,colour_lightgrey, colour_dimBlack , 30);
        menuQuit.setPosition((window.getSize().x/2)-(pvpButton.getSize().x/2),(window.getSize().y*0.3334)+(window.getSize().y*0.30));
        
        
        //*</Creating Button>


        //*Creating shapes for Puase button Image
        rect1.setFillColor(sf::Color::White);
        rect1.setSize(sf::Vector2f(5,15));
        rect1.setPosition(sf::Vector2f(2,2));
        
        rect2.setFillColor(sf::Color(0,0,0,0));
        rect2.setSize(sf::Vector2f(5,15));
        rect2.setPosition(sf::Vector2f(7,2));

        rect3.setFillColor(sf::Color::White);
        rect3.setSize(sf::Vector2f(5,15));
        rect3.setPosition(sf::Vector2f(12,2));
        //*</Pause button image>


        //* Error message if wrong cell selection
        sf::Text error;
        error.setString("Try an empty cell.");
        error.setFont(font);
        error.setPosition(window.getSize().x/2,200);
        //*</Error>


        





        //! MENU
        if(Game_mode == 0){
            
            //*Menu Background
            sf::RectangleShape Menu;
            Menu.setSize(sf::Vector2f(
                
                window.getSize().x*0.90,
                window.getSize().y*0.90)
                
                );
            Menu.setFillColor(sf::Color(128, 128, 128,255));
            Menu.setPosition(sf::Vector2f(
                
                window.getSize().x*0.06,
                window.getSize().y*0.06
                )
                );
            //*</Menu Background>

            bool exit_menu = false;

            //*Main Headint
            sf::Text Heading;
            Heading.setFillColor(sf::Color(255, 255, 255, 255));
            Heading.setFont(font);
            Heading.setStyle(sf::Text::Bold);
            Heading.setStyle(sf::Text::Underlined);
            Heading.setCharacterSize(60);
            Heading.setString("     Tic Tac Toe     ");
            Heading.setPosition(sf::Vector2f((window.getSize().x/2)-(Heading.getLocalBounds().width/2),window.getSize().y*0.1667));
            //*</Heading>


            
            
            //*Event Handling
            sf::Event event;
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed){
                    window.close();
                }

                if(event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(pvpButton.isPressed(sf::Mouse::getPosition(window))){
                            Game_mode = 2;
                            exit_menu = true;
                        }
                        if(pvAIButton.isPressed(sf::Mouse::getPosition(window))){
                            Game_mode = 1;
                            exit_menu = true;
                        }
                        if(menuQuit.isPressed(sf::Mouse::getPosition(window))){
                            window.close();
                            exit_menu = true;
                        }
                    }
                }
                if(exit_menu == true){
                    continue;
                }
            }

            window.clear(sf::Color::Black);

            window.draw(Menu);

            window.draw(Heading);

            pvpButton.draw(window);
            pvAIButton.draw(window);
            menuQuit.draw(window);


            window.display();
            

        }
        
        //! IF Pvs(AI)
        else if(Game_mode == 1){

            //^Selecting which (p or pc) have a turn.
            if(turn%2 == 0){
                
                symbol = p1Symbol;
                
                playerTurn.setString("Player's Turn");
                playerTurn.setPosition(((window.getSize().x/2)-(playerTurn.getLocalBounds().width/2)),20);

            }else{
                
                
                symbol = compSymbol;
                

                playerTurn.setString("Computer's Turn");
                playerTurn.setPosition(((window.getSize().x/2)-(playerTurn.getLocalBounds().width/2)),20);
                
                }
            

            
            //^Event Loop
            sf::Event event;
            while(window.pollEvent(event)){
            
                //^CHeck if user clicks close button.
                if(event.type == sf::Event::Closed){
                    window.close();
                }

                //^ If computer's turn use AI.
                if(symbol == compSymbol){

                    VAI(cells,compChoice,buttonstate);

                    // AI(buttonstate, symbol);
                    turn++;
                
                }
                
                //^ If left click registerd, check Which button was pressed.
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left){
                        if(button00.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[0] == ""){

                                buttonstate[0] = symbol;
                                turn++;
                            }else{
                                
                                window.draw(error);
                            }
                        }
                        else if(button01.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[1] == ""){

                                buttonstate[1] = symbol;
                                turn++;
                            }else{
                                
                                window.draw(error);
                            }
                        }
                        else if(button02.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[2] == ""){

                            buttonstate[2] = symbol;
                            turn++;
                            }else{
                                
                                window.draw(error);
                            }
                        }
                        else if(button10.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[3] == ""){

                                buttonstate[3] = symbol;
                                turn++;
                            }else{
                                
                                window.draw(error);
                            }
                        }
                        else if(button11.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[4] == ""){

                                buttonstate[4] = symbol;
                                turn++;
                            }else{
                                
                                window.draw(error);
                            }
                        }
                        else if(button12.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[5] == ""){

                                buttonstate[5] = symbol;
                                turn++;
                            }else{
                                
                                window.draw(error);
                            }
                        }
                        else if(button20.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[6] == ""){

                                buttonstate[6] = symbol;
                                turn++;
                            }else{
                                
                                window.draw(error);
                            }
                        }
                        else if(button21.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[7] == ""){

                                buttonstate[7] = symbol;
                                turn++;
                            }else{
                                window.draw(error);
                            }
                        }
                        else if(button22.isPressed(sf::Mouse::getPosition(window))){
                            if(buttonstate[8] == ""){

                                buttonstate[8] = symbol;
                                turn++;
                            }else{
                                
                                window.draw(error);
                            }
                        }
                        else if(pause_button.isPressed(sf::Mouse::getPosition(window))){
                            paused = true;
                            while(paused){

                                sf::Event pauseEvent;
                                while(window.pollEvent(pauseEvent)){
                                    if(pauseEvent.type == sf::Event::Closed){
                                        window.close();
                                        paused = false;
                                    }
                                }

                                window.clear(sf::Color::Black);
                                pauseMenu(window,font,playerWins,compWins,Cdraws,paused,Game_mode);
                                window.display();
        }                   
        
                        }
                        else{}
                        



                    }//close if of "WHich " button pressed
                    
                    }//Clossing if a button pressed
                    else{}



            }//EVen while close

            
        

            //Check if Someone Won
            bool result = winchecklogic(buttonstate, symbol[0]);
            
            //If comeone Won
            if(result){
                //Updates variables accoring to who won
                string whoWon = who_Won(result, symbol[0], Pdraws, compWins, playerWins, compLoss, playerLoss);
                //reset turn count
                turn = 0;
                //reset board.
                for(int i = 0; i<9 ; i++){
                        buttonstate[i] = "";
                    }
                bool isPaused = true;
                while(isPaused){
                    sf::Event pauseEvent;
                    while(window.pollEvent(pauseEvent)){
                        if(pauseEvent.type == sf::Event::Closed){
                            window.close();
                            isPaused = false;
                        }
                    }
                window.clear(sf::Color::Black);
                pauseMenu(window,font,playerWins,compWins,Pdraws,isPaused,Game_mode);
                window.display();
                }
        }
            


            

        
            



            //*Update window
            window.clear(sf::Color::Black);
            //*</Update Window>

            //*Table Display.
            window.draw(Vline1); 
            window.draw(Vline2);

            window.draw(Hline1); 
            window.draw(Hline2);

            //*</Table>


            
            //*Display turn
            window.draw(playerTurn);
            //*</Display Tunr>


            //*Buttons
            button00.draw(window);
            button01.draw(window);
            button02.draw(window);
            button10.draw(window);
            button11.draw(window);
            button12.draw(window);
            button20.draw(window);
            button21.draw(window);
            button22.draw(window);
            //*</Buttons>

            //*Pause Button
            window.draw(rect1);
            window.draw(rect2);
            window.draw(rect3);
            pause_button.draw(window);
            //*</Pause Button>

            window.display();

        }// P vs AI IF close        
    
        
    //! Player v Player
        else if(Game_mode == 2){
        //^Selecting which (p or pc) have a turn.
        if(turn%2 == 0){
            symbol = p1Symbol;
            playerTurn.setString("First Player's Turn");
            playerTurn.setPosition(((window.getSize().x/2)-(playerTurn.getLocalBounds().width/2)),20);
        }else{
            symbol = compSymbol;
            playerTurn.setString("Second Player's Turn");
            playerTurn.setPosition(((window.getSize().x/2)-(playerTurn.getLocalBounds().width/2)),20);
        }

        //^Event Loop
        sf::Event event;
        while(window.pollEvent(event)){
            //^CHeck if user clicks close button.
            if(event.type == sf::Event::Closed){
                window.close();
            }
            //^ If left click registerd, check Which button was pressed.
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left){
                    if(button00.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[0] == ""){
                            if(symbol == compSymbol){
                                buttonstate[0] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[0] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(button01.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[1] == ""){
                            if(symbol == compSymbol){
                                buttonstate[1] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[1] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(button02.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[2] == ""){
                            if(symbol == compSymbol){
                                buttonstate[2] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[2] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(button10.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[3] == ""){
                            if(symbol == compSymbol){
                                buttonstate[3] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[3] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(button11.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[4] == ""){
                            if(symbol == compSymbol){
                                buttonstate[4] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[4] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(button12.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[5] == ""){
                            if(symbol == compSymbol){
                                buttonstate[5] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[5] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(button20.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[6] == ""){
                            if(symbol == compSymbol){
                                buttonstate[6] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[6] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(button21.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[7] == ""){
                            if(symbol == compSymbol){
                                buttonstate[7] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[7] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(button22.isPressed(sf::Mouse::getPosition(window))){
                        if(buttonstate[8] == ""){
                            if(symbol == compSymbol){
                                buttonstate[8] = compSymbol;
                                turn++;
                            }
                            else{
                                buttonstate[8] = p1Symbol;
                                turn++;
                            }
                        }
                    }
                    else if(pause_button.isPressed(sf::Mouse::getPosition(window))){
                        paused = true;
                        while(paused){
                            sf::Event pauseEvent;
                            while(window.pollEvent(pauseEvent)){
                                if(pauseEvent.type == sf::Event::Closed){
                                    window.close();
                                    paused = false;
                                }
                            }
                            window.clear(sf::Color::Black);
                            pauseMenu(window,font,playerWins,compWins,Cdraws,paused,Game_mode);
                            window.display();
                        }
                    }
                } //close if of "WHich " button pressed
            } //Clossing if a button pressed
        } //EVen while close

        //Check if Someone Won
        bool result = winchecklogic(buttonstate, symbol[0]);
        //If comeone Won
        if(result){
            //Updates variables accoring to who won
            string whoWon = who_Won(result, symbol[0], Pdraws, compWins, playerWins, compLoss, playerLoss);
            //reset turn count
            turn = 0;
            //reset board.
            for(int i = 0; i<9 ; i++){
                buttonstate[i] = "";
            }
            bool isPaused = true;
            while(isPaused){
                sf::Event pauseEvent;
                while(window.pollEvent(pauseEvent)){
                    if(pauseEvent.type == sf::Event::Closed){
                        window.close();
                        isPaused = false;
                    }
                }
                window.clear(sf::Color::Black);
                pauseMenu(window,font,playerWins,compWins,Pdraws,isPaused,Game_mode);
                window.display();
            }
        }

        //*Update window
        window.clear(sf::Color::Black);
        //*</Update Window>

        //*Table Display.
        window.draw(Vline1); 
        window.draw(Vline2);
        window.draw(Hline1); 
        window.draw(Hline2);
        //*</Table>

        //*Display turn
        window.draw(playerTurn);
        //*</Display Tunr>

        //*Buttons
        button00.draw(window);
        button01.draw(window);
        button02.draw(window);
        button10.draw(window);
        button11.draw(window);
        button12.draw(window);
        button20.draw(window);
        button21.draw(window);
        button22.draw(window);
        //*</Buttons>

        //*Pause Button
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        pause_button.draw(window);
        //*</Pause Button>
        window.display();
    }


        } //Game Loop 
} // Main Loop  
