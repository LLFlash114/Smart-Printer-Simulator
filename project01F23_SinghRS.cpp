/*-------------------------------------------
// Course: COMP 150
// Last Name: Singh
// First Name: Rajveer
// Student ID: 300202522
// 
// File: project01F23_SinghRS

// Summary: Simulates the functionalities of a smart printer such as 
			printing, scanning, copying documents, setting config, and holdng
			documents in queues 
*-------------------------------------------*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;



/*int mainMenu();*/
// Function prototypes
void detectUSB();
void documentScanCheck();
void collectGeneralData(string &filename, string &print_layout, string &document_color, int &ink_choice);
void inputError(int &input, int x, int y);
void inkCheck(int &color_ink, int &black_ink);
void paperCheck(int &num_paper);
void openQueue(string array[], int &array_size);
void addToArray(string array[], int &array_size, string new_item);
void addToArray(int array[], int &array_size, int new_item);
void deleteQueueEntry(string array[], int &array_size, int entry);
void deleteQueueEntry(int array[], int &array_size, int entry);


// Global variables
const int MAX_QUEUE_SIZE = 800;

int main()
{
	
	// Storing file configuration and user input
	string title, printer1, printer2, printer3, printer4, printer5, printer6, printer7, printer8, printer9, printer_tray1, printer_tray2, printer_top, printer_bottom, printer,
		filename, user_cloud, document_type, scan_data, user_email, output_type, copy_data, document_color, scan_destination_name, option1, customize_printer, config_data, 
		print_layout, filename_display, copies_display;

	bool scan_again=true, back=false, exit=false;
	
	int num_black_ink=80, num_color_ink=80, num_paper=200, user_operation, print_device, print_choice, print_copies=0, current_size=0, current_scan_size=0, user_choice, device_choice, 
		ink_choice, opened_queue, design_choice, customize_choice;
	
	// Arrays
	string devices[] = {"Computer", "Laptop", "Phone", "Phone2", "Tablet", "USB"};
	string scan_devices[] = {"Computer", "Laptop", "Phone", "Email", "Cloud", "USB"};
	
	string print_queue[MAX_QUEUE_SIZE];
	string output_print_queue[MAX_QUEUE_SIZE];
	string scan_queue[MAX_QUEUE_SIZE];
	string output_scan_queue[MAX_QUEUE_SIZE];
	int paper_color[MAX_QUEUE_SIZE];
	
	// Loading output file
	ofstream outputfile;
	outputfile.open("project01output.txt");
	
	
	// Storing program title	 				                                                                        
	title = "   _____                      __     ____       _       __               ____             __        __\n"                 
  			"  / ___/____ ___  ____ ______/ /_   / __ \\_____(_)___  / /____  _____   / __ \\_________  / /_____  / /___  ______  ___\n" 
  			"  \\__ \\/ __ `__ \\/ __ `/ ___/ __/  / /_/ / ___/ / __ \\/ __/ _ \\/ ___/  / /_/ / ___/ __ \\/ __/ __ \\/ __/ / / / __ \\/ _ \\ \n"
 			" ___/ / / / / / / /_/ / /  / /_   / ____/ /  / / / / / /_/  __/ /     / ____/ /  / /_/ / /_/ /_/ / /_/ /_/ / /_/ /  __/\n"
			"/____/_/ /_/ /_/\\__,_/_/   \\__/  /_/   /_/  /_/_/ /_/\\__/\\___/_/     /_/   /_/   \\____/\\__/\\____/\\__/\\__, / .___/\\___/\n" 
            "                                                                                                    /____/_/\n";
	
	// Storing printer ASCII ART
  	printer_top = "      ---------(printer top)--------\n";
	printer1 = ",----,------------------------------,------.\n";
  	printer2 = "| ## |                              |    - |\n";
  	printer3 = "| ## |                              |    - |\n";
  	printer4 = "|    |------------------------------|    - |\n";
  	printer5 = "|    ||............................||      |\n";
  	printer6 = "|    ||,-                        -.||      |\n";
  	printer_tray1 = "|    ||,-  (output tray above)   -.||      |\n";
  	printer_tray2 = "|    ||___ (output tray below)  ___||    ##|\n";
  	printer7 = "|    ||___                      ___||    ##|\n";
  	printer8 = "|    ||---`--------------------'---||      |\n";
  	printer9 = "`----'|_|______________________==__|`------'\n";
  	printer_bottom = "      -------(printer bottom)-------";

	// Shows printer customization options
	customize_printer = printer_top + printer1 + printer2 + printer3 + printer4 + printer5 + printer_tray1 + printer_tray2 + printer8 + printer9 + printer_bottom;
	printer = printer1 + printer2 + printer3 + printer4 + printer5 + printer6 + printer7 + printer8 + printer9; 
	
	
	
	
	
	// Outputting title and welcome message
	cout << title << endl;
	cout << "\n\n================================================================================================================" << endl;
	cout << "\t\t# This a prototype program that simulates some functions of our Smart Printer #" << endl;
	cout << "\n---> Simulates 3 modes of usage: PRINTING, SCANNING, and COPYING" << endl;
	cout << "---> Supports printing and scan jobs to be stored in a queue" << endl;
	cout << "---> Includes customizer options for the printer and some pages" << endl;
	cout << "---> Includes some maintenance and troubleshooting functions" << endl;
	cout << "\nNOTE: not all mode config options/settings included for the sake of simplicity (paper size, margin, etc)" << endl;
	cout << "================================================================================================================\n\n\n\n" << endl; 
	
	// Outputting printer ASCII art
	cout << "\n\t\t [PRINTER]" << endl;
	cout << printer << endl;
	
	// Outputting Main Menu
	while (user_operation != 6)
	{	
	cout << "\n\n\n==========================================" << endl;
	cout <<	"\t\t*MAIN MENU*" << endl;
	cout << "\n[WI-FI]: CONNECTED" << "\t[BLACK INK]: " << num_black_ink << endl;
	cout << "[PAPER LOADED]: " << num_paper << "\t[COLOR INK]: " << num_color_ink << endl;
	cout << "\n1. Print Documents\n"
			"2. Scan Documents\n"
			"3. Copy Documents\n"
			"4. View Queues\n"
			"5. Customize Printer\n"
			"6. Exit and print queues/printer graphic" << endl;
	cout << "\n==========================================" << endl;
	cout << "OPERATION: (type a num 1-6):  ";
	
	cin >> user_operation;
	inputError(user_operation, 1, 6);
	cout << "==========================================" << endl;
	
	
	// Performing user selected printer operation
	switch(user_operation)
	{
		case 1:	// Print documents operation
			cout << "\n\nSelect the device to print from: (type num)" << endl;
			cout << "\n1) Computer\t2) Laptop\t3) Phone\n"
					"4) Phone2\t5) Tablet\t6) USB" << endl;
			cout << "\nDevice: ";
			cin >> device_choice;
			inputError(device_choice, 1, 6); // error checking
			
			// Simulating USB inseration
			if (device_choice == 6)
			{
				detectUSB();
			}
			cout << "\n\n\n----------------Printing from " << devices[device_choice-1] << "----------------" << endl << endl;
			
			// Gathering document print configuration 
			collectGeneralData(filename, print_layout, document_color, ink_choice);
			cout << "\nEnter the number of copies to print (1 or more): ";
			cin >> print_copies;
			while (print_copies < 1) // error checking
			{	
				cout << "\n******************************"  << endl;
				cout << "ERROR: Invalid value entered" << endl;
				cout << "******************************" << endl;
				cout << "Type a num that is 1 or greater:  ";
				cin >> print_copies;
			}
			cout << "----------------" << endl;
	
			// Formatting and storing on configuration into 1 string
			config_data = print_layout + "  [Filename]: " + filename + " [Color]: " + document_color + " [Source Device]: " + devices[device_choice-1];
			cout << "\n\t Print configuration complete..." << endl;
			cout << "-------------------------------------------------" << endl;
		
			cout << "\nPrint document now or add to PRINT QUEUE?" << endl;
			cout << "1) Print now    2) Add to queue    3) Cancel " << endl;
			cout << "\nChoice:  ";
			cin >> user_choice;
			inputError(user_choice, 1, 3); // error checking
			
			// Printing document to output file
			if (user_choice == 1)
			{
				cout << "\n\n=====================================" << endl;
				cout << "Printing document(s)...." << endl;
				cout << "Documents printed" << endl;
				cout << "=====================================" << endl;
				while (print_copies != 0)
				{
					outputfile << "{PRINT OPERATION}" << endl;
					outputfile << config_data << endl << endl << endl;;
					inkCheck(num_color_ink, num_black_ink);	// error checking
					paperCheck(num_paper);	// error checking
					if (ink_choice == 1)
					{
						num_color_ink -= 1;
					}
					else
					{
						num_black_ink -= 1;
					}
					num_paper -= 1;
					print_copies -= 1;
				}
			}
			// Storing document to PRINT QUEUE
			else if (user_choice == 2)
			{
				cout << "\n\n=====================================" << endl;
				cout << "Adding document(s) to PRINT QUEUE...." << endl;
				cout << "Documents added" << endl;
				cout << "=====================================" << endl;
				while (print_copies != 0)
				{
					current_size++;
					addToArray(print_queue, current_size, filename);
					addToArray(output_print_queue, current_size, config_data);
					addToArray(paper_color, current_size, ink_choice);
					print_copies -= 1;
				}
			}
			// Cancelling printing operation and returning to MAIN MENU
			else {
					cout << "\nCancelling...." << endl;
					cout << "Returning to MAIN MENU..." << endl; 
					break;
				 }
			cout << "\nReturning to MAIN MENU..." << endl;
			break;
			
			
		case 2: // Scan documents operation
			scan_again = true; 
			while (scan_again == true)
				{
					// Simulating a physical scan and determining destination device
					documentScanCheck();
					cout << "\n\nSelect destination device to scan to: (type num)" << endl;
					cout << "\n1) Computer\t2) Laptop\t3) Phone\n"
							"4) Email\t5) Cloud\t6) USB" << endl;
					cout << "\nDevice:  ";
					cin >> device_choice;
					inputError(device_choice, 1, 6); // error checking
					
					if (device_choice == 4) // Email destination
					{
						cout << "\nEnter the email address to send the document to: ";
						cin.ignore();
						getline(cin, scan_destination_name); 
					}
					else if (device_choice == 5) // Cloud service destination
					{
						cout << "\nSelect the cloud service to send the document to: " << endl;
						cout << "1) Google Drive    2) Dropbox    3) OneDrive" << endl;
						cin >> user_choice;
						if (user_choice == 1)
						{
							scan_destination_name = "Google Drive";
						}
						else if (user_choice == 2)
						{
							scan_destination_name = "Dropbox";
						}
						else
						{
							scan_destination_name = "OneDrive";
						}
					}
					else if (device_choice == 6) // USB destination
					{
						detectUSB(); // USB simulation
						scan_destination_name = "USB";
					}
					else
					{
						scan_destination_name = scan_devices[device_choice - 1];
					}
					cout << "\n\n\n----------------Scanning to " << scan_destination_name << "----------------" << endl;
					
					// Gathering document scan configuration
					collectGeneralData(filename, print_layout, document_color, ink_choice);
					cout << "\nSelect document type (type a num 1-3)" << endl;
					cout << "1) Text    2) Text & Image    3) Photo" << endl;
					cout << "\nDocument type:  ";
					cin >> user_choice;
					inputError(user_choice, 1, 6); // error checking
					cout << "----------------" << endl;
					if (user_choice == 1)
					{		
						document_type = "Text";
					}
					else if (user_choice == 2)
					{
						document_type = "Text & Image";
					}
					else
					{
						document_type = "Photo";
					}
					
					cout << "\nSelect the output file type (type 1 or 2)" << endl;
					cout << "1) PDF    2) JPEG" << endl;
					cout << "\nFiletype:  ";
					cin >> user_choice;
					inputError(user_choice, 1, 2); // error checking
					cout << "----------------" << endl;
					if (user_choice == 1)
					{
						output_type = "PDF";
					}
					else
					{
						output_type = "JPEG";
					}		
			
					// Storing and formatting scan data into 1 string
					scan_data = print_layout + "  [Filename]: " + filename +  " [Document type]: " + document_type + " [Color]: " + document_color + " [Output file type]: " + output_type + "  -------> " + scan_destination_name;
			
					cout << "\nSend document now or add to SCAN QUEUE?" << endl;
					cout << "1) Send now    2) Add to queue    3) Cancel" << endl;
					cout << "\nChoice:  ";
					cin >> user_choice;
					inputError(user_choice, 1, 3); // error checking
					
					// Scanning document to output file
					if (user_choice == 1)
					{
						cout << "\n\n=========================================" << endl;
						cout << "Sending document to " << scan_destination_name << "...." << endl;
						cout << "Document sent" << endl;
						cout << "=========================================" << endl;
						outputfile << "{SCAN OPERATION}" << endl;
						outputfile << scan_data << endl << endl << endl;
					}
					// Scanning document to SCAN QUEUE
					else if (user_choice == 2)
					{
						cout << "\n\n=========================================" << endl;
						cout << "Adding document to SCAN QUEUE...." << endl;
						cout << "Document added" << endl;
						cout << "=========================================" << endl;
						filename_display = filename + " -----> " + scan_destination_name; // put this before the if statement probably
						current_scan_size++;
						addToArray(scan_queue, current_scan_size, filename_display);
						addToArray(output_scan_queue, current_scan_size, scan_data);
					}
					// Cancelling document scan and returning to MAIN MENU
					else
					{
						cout << "\nCancelling...." << endl;
						cout << "Returning to MAIN MENU..." << endl; 
						break;
					}
					
					// Prompting for another scan or return to MAIN MENU
					cout << "\nScan another document?" << endl;
					cout << "1) Scan another    2) MAIN MENU" << endl;
					cin >> user_choice;
					inputError(user_choice, 1, 2); // error checking
					if (user_choice == 1)
					{
						scan_again = true;
					}
					else
					{
						cout << "\nReturning to MAIN MENU..." << endl; 
						scan_again = false;
					}
				}
				
				// Returning to MAIN MENU 
				cout << "Returning to MAIN MENU..." << endl; 
				break;
			
			
		case 3:	// Copy document operation
			scan_again = true;
			while (scan_again == true)
			{
				// Simulating physical document scan
				documentScanCheck();
				cout << "\n\n\n----------------Copying document----------------" << endl;
				
				// Gathering copy document configuration
				collectGeneralData(filename, print_layout, document_color, ink_choice);
				cout << "\nEnter the number of copies to create (1 or more): ";
				cin >> print_copies;
				while (print_copies < 1) // error checking
				{	
					cout << "\n******************************"  << endl;
					cout << "ERROR: Invalid value entered" << endl;
					cout << "******************************" << endl;
					cout << "Type a num that is 1 or greater:  ";
					cin >> print_copies;
				}	
				cout << "----------------" << endl;
				
				// Storing and formatting copy configuration to 1 string
				copy_data = print_layout + "  Copy of [Filename]: " + filename + " [Color]: " + document_color;
				
				cout << "\nPrint copies now or add to PRINT QUEUE?" << endl;
				cout << "1) Print copies now    2) Add copies to queue    3) Cancel" << endl;
				cout << "\nChoice:  ";
				cin >> print_choice;
				inputError(print_choice, 1, 3); // error checking
				
				// Printing copy documents to output queue 
				if (print_choice == 1)
				{
					cout << "\n\n=====================================" << endl;
					cout << "Printing document(s)...." << endl;
					cout << "Documents printed" << endl;
					cout << "=====================================" << endl;
					while (print_copies != 0)
					{
						inkCheck(num_color_ink, num_black_ink); // error checking
						paperCheck(num_paper);	// error checking
						outputfile << copy_data << endl << endl << endl;
						if (ink_choice == 1)
						{
							num_color_ink -= 1;
						}
						else
						{
							num_black_ink -= 1;
						}
						num_paper -= 1;
						print_copies -= 1;
					}
				}
				// Adding copy documents to PRINT QUEUE
				else if (print_choice == 2)
				{
					cout << "\n\n=====================================" << endl;
					cout << "Adding document(s) to PRINT QUEUE...." << endl;
					cout << "Documents added" << endl;
					cout << "=====================================" << endl;
					copies_display = "Copy of " + filename; // move to before the if statement probably
					while (print_copies != 0)
					{
						current_size++;
						addToArray(print_queue, current_size, copies_display);
						addToArray(output_print_queue, current_size, copy_data);
						addToArray(paper_color, current_size, ink_choice);
						print_copies -= 1;
					}
				}
				// Cancelling copy operation and returning to MAIN MENU
				else
				{
					cout << "\nCancelling...." << endl;
					cout << "Returning to MAIN MENU..." << endl; 
					break;
				}
				
				// Prompting to copy another document or return to MAIN MENU
				cout << "\nCopy another document?" << endl;
				cout << "1) Copy another    2) MAIN MENU" << endl;
				cin >> user_choice;
				inputError(user_choice, 1, 2); // error checking
				if (user_choice == 1)
				{
					scan_again = true;
				}
				else
				{
					cout << "\nReturning to MAIN MENU..." << endl;
					scan_again = false; 
				}
			}
			break;
			
			
		case 4:
			exit = false;
			// Looping until MAIN MENU is selected
			while (exit == false)
			{
				cout << "\n\nWhich QUEUE would you like to open?" << endl;
				cout << "1) Print    2) Scan    3) MAIN MENU" << endl;
				cout << "\nChoice:  ";
				cin >> opened_queue;
				inputError(opened_queue, 1, 3); // error checking
				back = false;
				// Looping until back is selected
				while (back == false)
				{
					// Opening PRINT QUEUE
					if (opened_queue == 1)
					{
						cout << "\nOpening print queue..." << endl;
						cout << "\n\n=================================================" << endl;
						cout << "  \t           PRINT QUEUE" << endl;
						cout << "=================================================" << endl;
						openQueue(print_queue, current_size);
						cout << "\n=================================================" << endl;
					}
					// OPENING SCAN QUEUE
					else if (opened_queue == 2) 
					{
						cout << "\nOpening scan queue..." << endl;
						cout << "\n\n=================================================" << endl;
						cout << "  \t           SCAN QUEUE" << endl;
						cout << "=================================================" << endl;
						openQueue(scan_queue, current_scan_size);
						cout << "\n=================================================" << endl;	
					}
					// Returning to MAIN MENU
					else
					{
						exit = true;
						break;
					}
			
					cout << "\nChoose an operation?" << endl;
					cout << "1) View entry    2) Delete entry    3) BACK" << endl;
					cout << "\nChoice:  ";
					cin >> user_choice;
					inputError(user_choice, 1, 3); // error checking
					
					// Viewing an entry
					if (user_choice == 1)
					{
						cout << "\nEnter a number to view an entry: ";
						cin >> user_choice;		// add error checking
						if (opened_queue == 1)
						{
							cout << endl << endl << output_print_queue[user_choice - 1];	
						}
						else
						{
							cout << endl << endl << output_scan_queue[user_choice - 1];
						}
					}
					// Deleting an entry
					else if (user_choice == 2)
					{
						cout << "\nEnter a number to delete an entry: ";
						cin >> user_choice;		// add error checking
						if (opened_queue == 1)
						{
							deleteQueueEntry(print_queue, current_size, user_choice);
							deleteQueueEntry(output_print_queue, current_size, user_choice);

							deleteQueueEntry(paper_color, current_size, user_choice);
							current_size--;
						}
				
						else
						{
							deleteQueueEntry(scan_queue, current_scan_size, user_choice);
							deleteQueueEntry(output_scan_queue, current_scan_size, user_choice);
							current_scan_size--;
						}
					}
					// Selecting BACK
					else
					{
						back = true;
						break;
					}
				}
			}
			break;
			
			
		case 5:	// Customization operation
			cout << "\n\n\n----------------Welcome to the Printer Customizer----------------" << endl;
			cout << "\n\n" << customize_printer;
			
			// Selecting the printer part to customize
			cout << "\n\nWhat part of the printer would you like to customize?" << endl;
			cout << "\n1. Printer top\n"
					"2. Printer output tray (top)\n"
					"3. Printer output tray (bottom)\n"
					"4. Printer bottom" << endl;
			cout << "\nChoice: ";
			cin >> customize_choice;
			inputError(customize_choice, 1, 4); // error checking
			
			// Selecting a design
			cout << "\nChoose from a design below" << endl;
			cout << "\n1. \"7_/\"7_/\"7_/\"7_/\"7_/\"7_/\"7_/\"\n\n"
					"2. _/~\\_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\_/\n\n"
					"3. =^..^==^..^==^..^==^..^==^..^==^..^==^..^=\n\n"
					"4. /^(o.o)^\\ /^(o.o)^\\ /^(o.o)^\\ /^(o.o)^\\" << endl;
			cout << "\nChoice: ";
			cin >> design_choice;
			inputError(design_choice, 1, 4); // error checking
			
			// Customizing the design for the part picked and design chosen
			switch(customize_choice)			
			{
				case 1: // Printer top
						if (design_choice == 1)
						{
							option1 = string(",----,") + string("\"7_/\"7_/\"7_/\"7_/\"7_/\"7_/\"7_/\"7") + string(",------.\n");
							printer1 = option1;
						}
						
						else if (design_choice == 2)
						{
							option1 = string(",----,") + string("_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\_/") + string(",------.\n");
							printer1 = option1;
						}
						else if (design_choice == 3)
						{
							option1 = string(",----,") + string("=^..^==^..^==^..^==^..^==^..^=") + string(",------.\n");
							printer1 = option1; 
						}
						else
						{
							option1 = string(",----,") + string("/^(o.o)^\\  /^(o.o)^\\ /^(o.o)^\\") + string(",------.\n");
							printer1 = option1;
						}
					break;
					
				case 2: // Printer output tray top
						if (design_choice == 1)
						{
							option1 = string("|    ||") + string("\"7_/\"7_/\"7_/\"7_/\"7_/\"7_//\"7/") + string("||      |\n");
							printer5 = option1;
						}
						else if (design_choice == 2)
						{
							option1 = string("|    ||") + string("_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\") + string("||      |\n");
							printer5 = option1;

						}
						else if (design_choice == 3)
						{
							option1 = string(",----,") + string("=^..^==^..^==^..^==^..^==^..^=") + string(",------.\n");
							printer5 = option1;
						}
						else
						{
							option1 = string(",----,") + string("/^(o.o)^\\  /^(o.o)^\\ /^(o.o)^\\") + string(",------.\n");
							printer5 = option1;
						}
					break;
					
				case 3:	// Printer output tray bottom
						if (design_choice == 1)
						{
							option1 = string("|    ||") + string("\"7_/\"7_/\"7_/\"7_/\"7_/\"7_//\"7/") + string("||      |\n");
							printer8 = option1;
						}
						else if (design_choice == 2)
						{
							option1 = string("|    ||") + string("_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\") + string("||      |\n");
							printer8 = option1;
						}
						else if (design_choice == 3)
						{
							option1 = string(",----,") + string("=^..^==^..^==^..^==^..^==^..^=") + string(",------.\n");
							printer8 = option1;
						}
						else
						{
							option1 = string(",----,") + string("/^(o.o)^\\  /^(o.o)^\\ /^(o.o)^\\") + string(",------.\n");
							printer8 = option1;
						}
					break;
					
				case 4: // Printer bottom
						if (design_choice == 1)
						{
							option1 = string("`----'|") + string("\"7_/\"7_/\"7_/\"7_/\"7_/\"7_//\"7/") + ("|`------'\n");
							printer9 = option1;
						}
						else if(design_choice == 2)
						{
							option1 = string("`----'|") + string("_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\_/~\\") + string("|`------'\n");
							printer9 = option1;
						}
						
						else if (design_choice == 3)
						{
							option1 = string(",----,") + string("=^..^==^..^==^..^==^..^==^..^=") + string(",------.\n");
							printer9 = option1;
						}
						else
						{
							option1 = string(",----,") + string("/^(o.o)^\\  /^(o.o)^\\ /^(o.o)^\\") + string(",------.\n");
							printer9 = option1;
						}
					break;
				}
				
				// Updating the printer to hold the new design and outputting it
				printer = printer1 + printer2 + printer3 + printer4 + printer5 + printer6 + printer7 + printer8 + printer9;
				customize_printer = printer_top + printer1 + printer2 + printer3 + printer4 + printer5 + printer_tray1 + printer_tray2 + printer8 + printer9 + printer_bottom;
				cout << "\n\n" << printer << endl;
				break;
				
				
		case 6:	// Exit and output to file operation
			cout << "\n=========================================" << endl;
			cout << "Processing all queue items..." << endl;
			cout << "BOTH QUEUES AND PRINTER GRAPHIC PROCESSED" << endl;
			cout << "=========================================" << endl;
			
			// Outputting PRINT QUEUE entries to the output file
			outputfile << "\n--Print Queue items--" << endl;
			for (int i = 0; i < current_size; i++)
			{
				inkCheck(num_color_ink, num_black_ink); // error checking
				paperCheck(num_paper); // error checking
				outputfile << output_print_queue[i] << endl << endl;
				if (paper_color[i] == 1)
				{
					num_color_ink -= 1;
				}
				else
				{
					num_black_ink -= 1;
				}
				
				num_paper -= 1;     
			}
			
			// Outputting SCAN QUEUE entries to the output file
			outputfile << "\n--Scan Queue items--" << endl;
			for (int i = 0; i < current_scan_size; i++)
			{
				inkCheck(num_color_ink, num_black_ink); // error checking
				paperCheck(num_paper); // error checking
				outputfile << output_scan_queue[i] << endl << endl;
				if (paper_color[i] == 1)
				{
					num_color_ink -= 1;
				}
				else
				{
					num_black_ink -= 1;
				}
				
				num_paper -= 1;     
			}
			
			// Outputting the printer graphic to the output file
			outputfile << "\n\n-----Printer Graphic-----" << endl;
			outputfile << printer << endl << endl;
			
			// Exit message
			cout << "\n=========================================" << endl;
			cout << "PROGRAM TERMINATED" << endl;
			cout << "=========================================" << endl;	
	} // End of operations switch	
	
	} // End of MAIN MENU loop
	
	return 0;
	
	
}

// Functions

/*----------------------------------------------------------*/
/* This function simulates inserting a USB to a printer		*/
/* Preconditions: none										*/
/* Postcondition: none										*/  
void detectUSB()
{
	// Declarations
	string usb_art;
	char print_usb;
	
	// Storing ASCII art of USB
	usb_art = " _   ,--()\n"
  			  "( )-'-.------|>\n"
   			  "       `--[]";
	
	cout << "\n\n\t  ----Insert USB----" << endl;
	cout << "Have you inserted a USB? (type Y or N): ";  
	cin >> print_usb;
	
	// Error checking
	while (print_usb != 'Y' || print_usb == 'N')			
	{
		cout << "\t  ----USB NOT DETECTED----" << endl;
		cout << "\t  ----insert USB again--" << endl;
		cout << "Have you inserted a USB? (tpye Y or N): ";  
		cin >> print_usb;
	}
	
	cout << "\n\t ----USB DETECTED----" << endl;
}

/*----------------------------------------------------------*/
/* This function simulates inserting a paper to a printer	*/
/* Preconditions: none										*/
/* Postcondition: none										*/
void documentScanCheck()
{
	// Declarations
	char document_check;
	
	cout << "\n\n\t  ----Insert document----" << endl;
	cout << "Have you inserted a document? (type Y or N): ";  
	cin >> document_check;
				
	// Error checking
	while (document_check != 'Y' || document_check == 'N')			
	{
		cout << "\t  ----DOCUMENT NOT DETECTED----" << endl;
		cout << "\t  ----insert DOCUMENT again--" << endl;
		cout << "Have you inserted a Document? (type Y or N): ";  
		cin >> document_check;
	}
	
	cout << "\n\t ----DOCUMENTED DETECTED----" << endl;
}

/*----------------------------------------------------------*/
/* This function gathers general configuration for documents*/
/* Preconditions: filename, print_layout, document_color
				  ink choice
				  										    */
/* Postcondition: changes the values of preconditions	    */
void collectGeneralData(string &filename, string &print_layout, string &document_color, int &ink_choice)
{
	// Declarations
	string portrait_paper, landscape_paper;
	int user_choice;
	
	portrait_paper = ".-----------------------.\n"
					 "|                       |\n"
			   	     "|                       |\n"
				     "|                       |\n"
				     "|                       |\n"		
					 "|                       |\n"	
					 "|                       |\n"
					 "|                       |\n"
					 "|                       |\n"
					 "|                       |\n"
					 "|                       |\n"    
					 "|                       |\n"
					 "|                       |\n"    
					 "|                       |\n"
					 "|                       |\n"    
					 "'-----------------------'\n";
						  
	landscape_paper = " ________________________________\n"
					  "|                                |\n"
					  "|                                |\n"
					  "|                                |\n"
				      "|                                |\n"
				      "|                                |\n"
					  "|                                |\n"
					  "|                                |\n"
			          "|                                |\n"
					  "|________________________________|\n";
	 					  
	
	// Getting the filename 					   					  
	cout << "Enter the filename: ";
	cin.ignore();
	getline(cin, filename);
	
	// Getting the color choice
	cout << "\nSelect document color (type 1 or 2)" << endl;
	cout << "1) Color    2) Black and White" << endl;
	cout << "\nColor choice:  ";
	cin >> ink_choice;
	inputError(ink_choice, 1, 2); // error checking
	cout << "----------------" << endl;
	if (ink_choice == 1)
	{
		document_color = "Color";
	}
	else
	{
		document_color = "Black and White";
	}
	
	// Getting the orientation/layout
	cout << "\nSelect the layout (type 1 or 2)" << endl;
	cout << "1) Portrait    2) Landscape" << endl;
	cout << "\nLayout choice: ";
	cin >> user_choice;
	inputError(user_choice, 1, 2); // error checking
	cout << "----------------" << endl;
	if (user_choice == 1)
	{
		print_layout = portrait_paper;
	}
	else
	{
		print_layout = landscape_paper;
	}		
}

/*----------------------------------------------------------*/
/* This function handles int range value errors        	 	*/
/* Preconditions: variable to check, 2 numbers for the range*/
/* Postcondition: none										*/
void inputError(int &input, int x, int y)
{
		while (!(input >= 0 && input <= y))
		{
			cout << "\n******************************"  << endl;
			cout << "ERROR: Invalid value entered" << endl;
			cout << "******************************"  << endl;
			cout << "Try again, type a num " << x << " - " << y << ":  ";
			cin >> input;
		}
}

/*----------------------------------------------------------*/
/* This function handles errors if the ink color runs out   */
/* Preconditions: number of color ink and black ink left    */
/* Postcondition: changes the values of color variables		*/
void inkCheck(int &color_ink, int &black_ink)
{
	char replace_ink;
						
	if (color_ink < 1 || black_ink < 1)
	{	
		replace_ink = 'N';
		while (replace_ink == 'N')
		{
			cout << "\nNO MORE INK LEFT, INSERT CARTRIDGE" << endl;
			cout << "Cartridge inserted? (type Y or N): ";
			cin >> replace_ink;
		}
		cout << "\n*****************" << endl;
		cout << "Ink Replaced" << endl;
		cout << "*****************" << endl;
		color_ink += 80;
		black_ink += 80;
	}
}

/*----------------------------------------------------------*/
/* This function handles errors if the paper runs out       */
/* Preconditions: number of printer paper remaining         */
/* Postcondition: changes the value of paper variable		*/
void paperCheck(int &num_paper)
{
	char replace_paper;
						
	if (num_paper < 1)
	{	
		replace_paper = 'N';
		while (replace_paper == 'N')
		{
			cout << "\nNO MORE PAPER LEFT, INSERT PAPER" << endl;
			cout << "Cartridge inserted? (type Y or N): ";
			cin >> replace_paper;
		}
		cout << "\n*****************" << endl;
		cout << "PAPER Replaced" << endl;
		cout << "*****************" << endl;
		num_paper += 200;
	}
}

/*--------------------------------------------------------------------*/
/* This function outputs all entres in an array and numbers them      */
/* Preconditions: array and current array size         		          */
/* Postcondition: ouputs all the array items	                      */
void openQueue(string array[], int &array_size)
{
	for (int i = 0, num = 1; i < array_size; i++, num++)
	{
		cout << num << ": " << array[i] << endl;    
	}
}

/*--------------------------------------------------------------------*/
/* This function adds an int item to the back of an int array         */
/* Preconditions: array and current array size       		          */
/* Postcondition: updates the array	              				      */
void addToArray(int array[], int &array_size, int new_item)
{
	if (array_size < MAX_QUEUE_SIZE)
	{
		array[array_size - 1] = new_item;
	}
}

/*--------------------------------------------------------------------*/
/* This function adds a string item to the back of a string array      */
/* Preconditions: array and current array size       		          */
/* Postcondition: updates the array	  								  */
void addToArray(string array[], int &array_size, string new_item)
{
	if (array_size < MAX_QUEUE_SIZE)
	{
		array[array_size - 1] = new_item;
	}
}

/*--------------------------------------------------------------------*/
/* This function deletes an int item of an int array      			  */
/* Preconditions: array, current array size, and item position        */
/* Postcondition: updates the array	  								  */
void deleteQueueEntry(string array[], int &array_size, int entry)		
{
	for (int i = entry; i < array_size; i++)
	{
		array[i-1] = array[i];
	}
}

/*--------------------------------------------------------------------*/
/* This function deletes a string item of a string array      		  */
/* Preconditions: array, current array size, and item position        */
/* Postcondition: updates the array	  								  */
void deleteQueueEntry(int array[], int &array_size, int entry)
{
	for (int i = entry; i < array_size; i++)
	{
		array[i-1] = array[i];
	}
}

	
