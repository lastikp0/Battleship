#include "terminalOutput.h"

#include <iostream>
#include <string>
#include <sstream>
#include <map>

void TerminalOutput::drawFields(Game& game)
{
    Coords first_size;
    Participant* first;

    Coords second_size;
    Participant* second;

    for (int i = 0; i < game.getParticipantCount() - 1; i += 2) {
        first = game.getParticipant(i);
        second = game.getParticipant(i + 1);
        
        first_size = first->field->getSize();
        second_size = second->field->getSize();

        std::string space = "";
        int pad_1;
        int pad_2;

        std::cout << "Participant " << i;
        if (first->isBot()) {
            std::cout << "(Bot):";
            pad_1 = 0;
            pad_2 = 3;
        } else {
            std::cout << "(Player):";
            pad_1 = 3;
            pad_2 = 0;
        }

        for (int j = 0; j < 20 + pad_1 + pad_2 - (first_size.x * 2); j++) {
            space += " ";
        }

        for (int j = 0; j < pad_2 + 1; j++) {
            std::cout << " ";
        }

        std::cout << "Participant " << i + 1;
        if (second->isBot()) {
            std::cout << "(Bot):" << std::endl;
        } else {
            std::cout << "(Player):" << std::endl;
        }

        int max_y = std::max(first_size.y, second_size.y);
        for (int y = 0; y < max_y; y++) {
            for (int x = 0; x < first_size.x; x++) {
                if (y < first_size.y) {
                    FieldCellStatus cell_status = first->field->getCellStatus({x, y});

                    if (cell_status == FieldCellStatus::ship) {
                        ShipSegmentStatus segment_status = first->field->getShipSegmentStatus({x, y});

                        if (segment_status == ShipSegmentStatus::intact) {
                            std::cout << "2 ";
                        } else if (segment_status == ShipSegmentStatus::damaged) {
                            std::cout << "1 ";
                        } else {
                            std::cout << "0 ";
                        }

                    } else if (cell_status == FieldCellStatus::empty) {
                        std::cout << "* ";
                    } else {
                        if (first->isBot()) {
                            std::cout << ". ";
                        } else {
                            if (first->field->isShip({x, y})) {
                                ShipSegmentStatus segment_status = first->field->getShipSegmentStatus({x, y});

                                if (segment_status == ShipSegmentStatus::intact) {
                                    std::cout << "2 ";
                                } else if (segment_status == ShipSegmentStatus::damaged) {
                                    std::cout << "1 ";
                                } else {
                                    std::cout << "0 ";
                                }
                            } else {
                                std::cout << ". ";
                            }
                        }
                    }
                } else {
                    std::cout << "  ";
                }
            }

            std::cout << space;
            
            for (int x = 0; x < second_size.x; x++) {
                if (y < second_size.y) {
                    FieldCellStatus cell_status = second->field->getCellStatus({x, y});

                    if (cell_status == FieldCellStatus::ship) {
                        ShipSegmentStatus segment_status = second->field->getShipSegmentStatus({x, y});

                        if (segment_status == ShipSegmentStatus::intact) {
                            std::cout << "2 ";
                        } else if (segment_status == ShipSegmentStatus::damaged) {
                            std::cout << "1 ";
                        } else {
                            std::cout << "0 ";
                        }

                    } else if (cell_status == FieldCellStatus::empty) {
                        std::cout << "* ";
                    } else {
                        if (second->isBot()) {
                            std::cout << ". ";
                        } else {
                            if (second->field->isShip({x, y})) {
                                ShipSegmentStatus segment_status = second->field->getShipSegmentStatus({x, y});

                                if (segment_status == ShipSegmentStatus::intact) {
                                    std::cout << "2 ";
                                } else if (segment_status == ShipSegmentStatus::damaged) {
                                    std::cout << "1 ";
                                } else {
                                    std::cout << "0 ";
                                }
                            } else {
                                std::cout << ". ";
                            }
                        }
                    }
                } else {
                    std::cout << "  ";
                }
            }
            
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
    

    if (game.getParticipantCount() % 2 == 1) {
        first = game.getParticipant(game.getParticipantCount() - 1);
        
        first_size = first->field->getSize();

        std::cout << "Participant " << game.getParticipantCount() - 1;
        if (first->isBot()) {
            std::cout << "(Bot):" << std::endl;
        } else {
            std::cout << "(Player):" << std::endl;
        }

        for (int y = 0; y < first_size.y; y++) {
            for (int x = 0; x < first_size.x; x++) {
                FieldCellStatus cell_status = first->field->getCellStatus({x, y});

                if (cell_status == FieldCellStatus::ship) {
                    ShipSegmentStatus segment_status = first->field->getShipSegmentStatus({x, y});

                    if (segment_status == ShipSegmentStatus::intact) {
                        std::cout << "2 ";
                    } else if (segment_status == ShipSegmentStatus::damaged) {
                        std::cout << "1 ";
                    } else {
                        std::cout << "0 ";
                    }

                } else if (cell_status == FieldCellStatus::empty) {
                    std::cout << "* ";
                } else {
                    if (first->isBot()) {
                        std::cout << ". ";
                    } else {
                        if (first->field->isShip({x, y})) {
                            ShipSegmentStatus segment_status = first->field->getShipSegmentStatus({x, y});

                            if (segment_status == ShipSegmentStatus::intact) {
                                std::cout << "2 ";
                            } else if (segment_status == ShipSegmentStatus::damaged) {
                                std::cout << "1 ";
                            } else {
                                std::cout << "0 ";
                            }
                        } else {
                            std::cout << ". ";
                        }
                    }
                }
            }
            
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}

void TerminalOutput::drawParticipant(Game& game, int index)
{
    if (index < 0 || index >= game.getParticipantCount()) {
        return;
    }

    Participant* participant = game.getParticipant(index);
    if (participant->isBot()) {
        return;
    }

    Coords field_size = participant->field->getSize();
    int ship_manager_size = participant->ship_manager->getUnusedShipSize() + participant->ship_manager->getUsedShipSize();

    std::cout << "Participant " << index << ":" << std::endl;
    int max_size = std::max(field_size.y, ship_manager_size);
    for (int y = 0; y < max_size; y++) {
        for (int x = 0; x < field_size.x; x++) {
            if (y < field_size.y) {
                FieldCellStatus cell_status = participant->field->getCellStatus({x, y});

                if (cell_status == FieldCellStatus::ship) {
                    ShipSegmentStatus segment_status = participant->field->getShipSegmentStatus({x, y});

                    if (segment_status == ShipSegmentStatus::intact) {
                        std::cout << "2 ";
                    } else if (segment_status == ShipSegmentStatus::damaged) {
                        std::cout << "1 ";
                    } else {
                        std::cout << "0 ";
                    }

                } else if (cell_status == FieldCellStatus::empty) {
                    std::cout << "* ";
                } else {
                    if (participant->field->isShip({x, y})) {
                        ShipSegmentStatus segment_status = participant->field->getShipSegmentStatus({x, y});

                        if (segment_status == ShipSegmentStatus::intact) {
                            std::cout << "2 ";
                        } else if (segment_status == ShipSegmentStatus::damaged) {
                            std::cout << "1 ";
                        } else {
                            std::cout << "0 ";
                        }
                    } else {
                        std::cout << ". ";
                    }
                }
            } else {
                std::cout << "  ";
            }
        }

        std::cout << "     ";
            
        if (y < ship_manager_size) {
            Ship* ship;
            std::string ship_type;
            int ship_index = participant->ship_manager->getUnusedShipSize();
            if (y < ship_index) {
                ship_index = y;
                ship = participant->ship_manager->getUnusedShip(ship_index);
                ship_type = "Unused ship ";
            } else {
                ship_index = y - ship_index;
                ship = participant->ship_manager->getUsedShip(ship_index);
                ship_type = "Used ship ";
            }

            std::cout << ship_type << ship_index << ": ";
            for (int i = 0; i < ship->getSize(); i++) {
                if (ship->getSegmentStatus(i) == ShipSegmentStatus::intact) {
                    std::cout << "2 ";
                } else if (ship->getSegmentStatus(i) == ShipSegmentStatus::damaged) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            }
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void TerminalOutput::drawMessage(std::string message)
{
    std::cout << message << std::endl;
}

void TerminalOutput::drawHelp(std::map<char, std::string>& commands)
{
    std::cout << "Help" << std::endl;
    for (auto [key, value]: commands) {
        std::cout << key << ": " << value << std::endl;
    }
}