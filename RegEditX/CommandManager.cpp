#include "stdafx.h"
#include "CommandManager.h"
#include "AppCommandBase.h"

bool CommandManager::CanUndo() const {
	return !_undoList.empty();
}

bool CommandManager::CanRedo() const {
	return !_redoList.empty();
}

void CommandManager::AddCommand(std::shared_ptr<AppCommandBase> command, bool execute) {
	_undoList.push_back(command);
	_redoList.clear();
	if (execute)
		command->Execute();
}

bool CommandManager::Undo() {
	if(!CanUndo())
		return false;

	auto cmd = _undoList.back();
	cmd->Undo();
	_redoList.push_back(cmd);
	_undoList.pop_back();
	return true;
}

bool CommandManager::Redo() {
	if(!CanRedo())
		return false;

	auto command = _redoList.back();
	command->Execute();
	_redoList.pop_back();
	_undoList.push_back(command);
	return true;
}

void CommandManager::Clear() {
	_undoList.clear();
	_redoList.clear();
}

AppCommandBase* CommandManager::GetUndoCommand() const {
	return _undoList.empty() ? nullptr : _undoList.back().get();
}

AppCommandBase* CommandManager::GetRedoCommand() const {
	return _redoList.empty() ? nullptr : _redoList.back().get();
}