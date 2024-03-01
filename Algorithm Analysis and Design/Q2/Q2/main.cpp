#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Input Validation
bool input_validation(string input, bool flag)
{
    for (int i = 0; i < (int)input.length(); i++)
    {
        if (isdigit(input[i]) == false && input != "-1")
        {
            return false;
        }
    }

    if (stoi(input) < -1 && flag == false)
    {
        return false;
    }

    if (stoi(input) < 0 && flag == true)
    {
        return false;
    }

    return true;
}

// The shipment processing function
void process(vector<int> shipments, vector<int> &batches, vector<int> &leftovers, int batch_litre_to_orange, vector<string> &shipments_in_batches)
{
    int shipment_index = 0, batch_index = 0;

    // Check if the shipments count is equal or less than the maximum batch count which is 6
    if (shipments.size() <= batches.size())
    {
        // It will use all the oranges in each shipments on each batch to maximize the juices
        for (int i = 0; i < (int)shipments.size(); i++)
        {
            if (shipments[i] >= batch_litre_to_orange)
            {
                batches[i] = batch_litre_to_orange;
                leftovers[i] = shipments[i] - batch_litre_to_orange;
            }
            else
            {
                batches[i] = shipments[i];
            }
            shipments_in_batches[i] = " S" + to_string(i + 1);
        }
        return;
    }

    int shipment_hold = 0;

    // If the shipments count is more than 6, then it will run the below while loop
    while (shipment_index < (int)shipments.size() && (batch_index + 1) <= (int)batches.size())
    {
        // This is the same situation where the remaining shipments are less than the remaining batches to be fill in
        if ((shipments.size() - (shipment_index + 1)) <= (batches.size() - (batch_index + 1)) && shipment_hold == 0)
        {
            for (int i = shipment_index; i < (int)shipments.size(); i++)
            {
                if (shipments[i] >= batch_litre_to_orange)
                {
                    batches[batch_index] = batch_litre_to_orange;
                    leftovers[i] = shipments[i] - batch_litre_to_orange;
                    shipments_in_batches[batch_index] += (" S" + to_string(i + 1));
                    batch_index++;
                }
                else
                {
                    batches[batch_index] = shipments[i];
                    shipments_in_batches[batch_index] += (" S" + to_string(i + 1));
                    batch_index++;
                }
            }

            return;
        }

        // This handles the additions of oranges in shipments to fullfil the maximum output to each batches
        if ((shipments[shipment_index] + shipment_hold) >= batch_litre_to_orange)
        {
            batches[batch_index] = batch_litre_to_orange;
            leftovers[shipment_index] = shipments[shipment_index] - (batch_litre_to_orange - shipment_hold);
            shipments_in_batches[batch_index] += (" S" + to_string(shipment_index + 1));
            shipment_index++;
            batch_index++;
            shipment_hold = 0;
        }
        else
        {
            if ((shipments.size() - (shipment_index + 1)) <= (batches.size() - (batch_index + 1)))
            {
                batches[batch_index] = shipments[shipment_index] + shipment_hold;
                shipments_in_batches[batch_index] += (" S" + to_string(shipment_index + 1));
                shipment_index++;
                batch_index++;
                shipment_hold = 0;
            }
            else
            {
                shipment_hold += shipments[shipment_index];
                shipments_in_batches[batch_index] += (" S" + to_string(shipment_index + 1));
                shipment_index++;
            }
        }
    }

    return;
}

int main()
{
    string input, batch_litre;
    int increment = 0, batch_litre_to_oranges;
    bool inputFlag = false;
    vector<int> shipments, batches(6, 0);
    vector<string> shipments_in_batches(6, "");

    // User input of amount of oranges in shipments
    while (input != "-1")
    {
        cout << "Enter the number of oranges in shipment " << increment + 1 << endl;
        cout << "(To next step, please enter -1)\n";
        cin >> input;
        while (!input_validation(input, inputFlag))
        {
            system("cls");
            cout << "Invalid input.\n"
                 << "Please enter the number of orange in shipment " << increment + 1 << endl;
            cin >> input;
        }

        increment++;
        system("cls");

        if (input != "-1")
        {
            shipments.push_back(stoi(input));
        }
    }

    inputFlag = true;

    // User input of amount of orange juice to be produced in each batch
    cout << "Enter the amount of orange juice to be produced in each batch => ";
    cin >> batch_litre;
    while (!input_validation(batch_litre, inputFlag))
    {
        system("cls");
        cout << "Invalid input.\n"
             << "Please enter the amount of orange juice to be produced in each batch.\n";
        cin >> input;
    }

    system("cls");

    // Output of the shipments that the user has input
    cout << "These are the shipments and amount of orange juice to be produced.\n_________\n";

    for (int i = 0; i < (int)shipments.size(); i++)
    {
        cout << "S" << i + 1 << " | " << shipments[i] << endl;
    }

    cout << "_________\n\n";

    // Output of the amount of orange juice to be produced that the user has input
    cout << "Amount of orange juice to be produced = " << batch_litre << " litres.\n";

    vector<int> leftovers(shipments.size(), 0);

    batch_litre_to_oranges = 14 * stoi(batch_litre);

    system("pause");
    system("cls");

    // Call the shipments processing function
    process(shipments, batches, leftovers, batch_litre_to_oranges, shipments_in_batches);

    float total = 0;

    // This is the output of orange juice produced in each batch
    cout << "The batches \n";
    for (int i = 0; i < (int)batches.size(); i++)
    {
        cout << "B" << i + 1 << " = " << batches[i] / (float)14 << " litres\n";
        total += batches[i] / (float)14;
    }
    cout << "Total = " << total << " litres\n";

    cout << endl;

    // This is the output of corresponding shipment of oranges used in the batch
    cout << "Shipments used in batches \n";
    for (int i = 0; i < (int)shipments_in_batches.size(); i++)
    {
        cout << "Shipments In Batches " << i + 1 << " = " << shipments_in_batches[i] << endl;
    }

    cout << endl;

    // This is the output of discarded oranges from each shipment
    cout << "The discarded oranges from each shipment \n";
    for (int i = 0; i < (int)leftovers.size(); i++)
    {
        cout << "Leftover" << i + 1 << " = " << leftovers[i] << " oranges\n";
    }

    cout << endl;

    return 0;
}
