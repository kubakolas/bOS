#include "CV.h"

bool CV::wait() {
	bool temp;
	if (pcb_waiting_list.front()->GetState() == State::ZAKONCZONY)
		temp = true;
	else
		temp = false;

	pcb_waiting_list.remove_if([](std::shared_ptr<PCB> proces) { if(proces->GetState() == State::ZAKONCZONY) return proces; });

	if (!(pcb_waiting_list.size() == 0)) {
		running->SetState(State::OCZEKUJACY);
	}
	pcb_waiting_list.push_back(running);

	return temp;
}
void CV::signal() {
	pcb_waiting_list.pop_front();
	pcb_waiting_list.remove_if([](std::shared_ptr<PCB> proces) { if (proces->GetState() == State::ZAKONCZONY) return proces; });

	if (pcb_waiting_list.size() > 0)
		pcb_waiting_list.front()->PCB::SetState(State::GOTOWY);
}
bool CV::is_empty() {
	if (pcb_waiting_list.size() == 0)
		return true;
	else
		return false;
}