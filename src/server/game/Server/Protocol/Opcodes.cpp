/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010 - 2012 ProjectSkyfire <http://www.projectskyfire.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "gamePCH.h"
/** \file
 \ingroup u2w
 */

#include "Opcodes.h"
#include "WorldSession.h"

/// Correspondence between opcodes and their names
OpcodeHandler opcodeTable[NUM_MSG_TYPES];

static void DefineOpcode(uint32 opcode, const char* name, SessionStatus status,
        PacketProcessing packetProcessing,
        void(WorldSession::*handler)(WorldPacket& recvPacket)) {
    opcodeTable[opcode].name = name;
    opcodeTable[opcode].status = status;
    opcodeTable[opcode].packetProcessing = packetProcessing;
    opcodeTable[opcode].handler = handler;
}

#define OPCODE( name, status, packetProcessing, handler ) DefineOpcode( name, #name, status, packetProcessing, handler )

void InitOpcodeTable() {
    for (int i = 0; i < NUM_MSG_TYPES; ++i) {
        DefineOpcode(i, "UNKNOWN", STATUS_NEVER, PROCESS_INPLACE,
                &WorldSession::Handle_NULL);
    }

    OPCODE( CMSG_WORLD_TELEPORT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE, 
            &WorldSession::HandleWorldTeleportOpcode);
    OPCODE( CMSG_TELEPORT_TO_UNIT, STATUS_LOGGEDIN, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CHECK_FOR_BOTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BOT_DETECTED2, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_FORCEACTIONSHOW, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PETGODMODE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GODMODE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DESTRUCTIBLE_BUILDING_DAMAGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHAR_CREATE, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCharCreateOpcode);
    OPCODE( CMSG_CHAR_ENUM, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCharEnumOpcode);
    OPCODE( CMSG_CHAR_DELETE, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCharDeleteOpcode);
    OPCODE( SMSG_CHAR_CREATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CHAR_ENUM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CHAR_DELETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_WORLD_LOGIN, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleWorldLoginOpcode);
    OPCODE( CMSG_PLAYER_LOGIN, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePlayerLoginOpcode);
    OPCODE( SMSG_NEW_WORLD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_TRANSFER_PENDING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_TRANSFER_ABORTED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CHARACTER_LOGIN_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOGIN_SETTIMESPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GAMETIME_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GAMETIME_SET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_GAMETIME_SET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GAMESPEED_SET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_GAMESPEED_SET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SERVERTIME, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SERVERTIME, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PLAYER_LOGOUT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePlayerLogoutOpcode);
    OPCODE( CMSG_LOGOUT_REQUEST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLogoutRequestOpcode);
    OPCODE( SMSG_LOGOUT_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOGOUT_COMPLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LOGOUT_CANCEL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLogoutCancelOpcode);
    OPCODE( SMSG_LOGOUT_CANCEL_ACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_NAME_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleNameQueryOpcode);
    OPCODE( SMSG_NAME_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PET_NAME_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetNameQuery);
    OPCODE( SMSG_PET_NAME_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GUILD_QUERY, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildQueryOpcode);
    OPCODE( SMSG_GUILD_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_COMMENTATOR_START_WARGAME, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_DB_REPLY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PAGE_TEXT_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePageTextQueryOpcode);
    OPCODE( CMSG_REQUEST_HOTFIX, STATUS_AUTHED, PROCESS_INPLACE,
            &WorldSession::HandleRequestHotFix);
    OPCODE( SMSG_PAGE_TEXT_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUEST_QUERY, STATUS_LOGGEDIN_OR_RECENTLY_LOGGOUT,
            PROCESS_INPLACE, &WorldSession::HandleQuestQueryOpcode);
    OPCODE( SMSG_QUEST_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GAMEOBJECT_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGameObjectQueryOpcode);
    OPCODE( SMSG_GAMEOBJECT_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CREATURE_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCreatureQueryOpcode);
    OPCODE( SMSG_CREATURE_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_WHO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleWhoOpcode);
    OPCODE( SMSG_WHO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_WHOIS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleWhoisOpcode);
    OPCODE( SMSG_WHOIS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CONTACT_LIST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleContactListOpcode);
    OPCODE( SMSG_CONTACT_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_FRIEND_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ADD_FRIEND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAddFriendOpcode);
    OPCODE( CMSG_DEL_FRIEND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleDelFriendOpcode);
    OPCODE( CMSG_SET_CONTACT_NOTES, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetContactNotesOpcode);
    OPCODE( CMSG_ADD_IGNORE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAddIgnoreOpcode);
    OPCODE( CMSG_DEL_IGNORE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleDelIgnoreOpcode);
    OPCODE( CMSG_GROUP_INVITE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupInviteOpcode);
    OPCODE( SMSG_GROUP_INVITE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GROUP_CANCEL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_GROUP_CANCEL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GROUP_ACCEPT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupAcceptOpcode);
    OPCODE( CMSG_GROUP_DECLINE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupDeclineOpcode);
    OPCODE( SMSG_GROUP_DECLINE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GROUP_UNINVITE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupUninviteOpcode);
    OPCODE( CMSG_GROUP_UNINVITE_GUID, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupUninviteGuidOpcode);
    OPCODE( SMSG_GROUP_UNINVITE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GROUP_SET_LEADER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupSetLeaderOpcode);
    OPCODE( SMSG_GROUP_SET_LEADER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LOOT_METHOD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLootMethodOpcode);
    OPCODE( CMSG_GROUP_DISBAND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupDisbandOpcode);
    OPCODE( SMSG_GROUP_DESTROYED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GROUP_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PARTY_MEMBER_STATS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PARTY_COMMAND_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GUILD_CREATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildCreateOpcode);
    OPCODE( CMSG_GUILD_INVITE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildInviteOpcode);
    OPCODE( SMSG_GUILD_INVITE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GUILD_ACCEPT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildAcceptOpcode);
    OPCODE( CMSG_GUILD_DECLINE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildDeclineOpcode);
    OPCODE( SMSG_GUILD_DECLINE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GUILD_INFO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildInfoOpcode);
    OPCODE( SMSG_GUILD_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GUILD_ROSTER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildRosterOpcode);
    OPCODE( SMSG_GUILD_ROSTER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GUILD_PROMOTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildPromoteOpcode);
    OPCODE( CMSG_GUILD_DEMOTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildDemoteOpcode);
    OPCODE( CMSG_GUILD_LEAVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildLeaveOpcode);
    OPCODE( CMSG_GUILD_REMOVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildRemoveOpcode);
    OPCODE( CMSG_GUILD_DISBAND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildDisbandOpcode);
    OPCODE( CMSG_GUILD_LEADER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildLeaderOpcode);
    OPCODE( CMSG_GUILD_MOTD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildMOTDOpcode);
    OPCODE( CMSG_QUERY_GUILD_REWARDS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildRewardsOpcode);
    OPCODE( CMSG_QUERY_GUILD_XP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildExperienceOpcode);
    OPCODE( CMSG_QUERY_GUILD_MAX_XP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildMaxExperienceOpcode);
    OPCODE( SMSG_GUILD_MAX_DAILY_XP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GUILD_XP_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GUILD_REWARDS_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GUILD_EVENT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GUILD_COMMAND_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MESSAGECHAT_SAY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_YELL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_CHANNEL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_WHISPER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_GUILD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_OFFICER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_AFK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_DND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_EMOTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_PARTY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_PARTY_LEADER, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_RAID, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_RAID_LEADER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_BATTLEGROUND, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_BATTLEGROUND_LEADER, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode);
    OPCODE( CMSG_MESSAGECHAT_RAID_WARNING, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleMessagechatOpcode);
    OPCODE( SMSG_MESSAGECHAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_JOIN_CHANNEL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleJoinChannel);
    OPCODE( CMSG_LEAVE_CHANNEL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLeaveChannel);
    OPCODE( SMSG_CHANNEL_NOTIFY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHANNEL_LIST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelList);
    OPCODE( SMSG_CHANNEL_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHANNEL_PASSWORD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelPassword);
    OPCODE( CMSG_CHANNEL_SET_OWNER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelSetOwner);
    OPCODE( CMSG_CHANNEL_OWNER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelOwner);
    OPCODE( CMSG_CHANNEL_MODERATOR, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelModerator);
    OPCODE( CMSG_CHANNEL_UNMODERATOR, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelUnmoderator);
    OPCODE( CMSG_CHANNEL_MUTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelMute);
    OPCODE( CMSG_CHANNEL_UNMUTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelUnmute);
    OPCODE( CMSG_CHANNEL_INVITE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelInvite);
    OPCODE( CMSG_CHANNEL_KICK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelKick);
    OPCODE( CMSG_CHANNEL_BAN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelBan);
    OPCODE( CMSG_CHANNEL_UNBAN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelUnban);
    OPCODE( CMSG_CHANNEL_ANNOUNCEMENTS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelAnnouncements);
    OPCODE( CMSG_CHANNEL_MODERATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_UPDATE_OBJECT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DESTROY_OBJECT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_USE_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleUseItemOpcode);
    OPCODE( CMSG_OPEN_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleOpenItemOpcode);
    OPCODE( CMSG_READ_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleReadItem);
    OPCODE( SMSG_READ_ITEM_OK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_READ_ITEM_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ITEM_COOLDOWN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GAMEOBJ_USE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGameObjectUseOpcode);
    OPCODE( CMSG_DESTROY_ITEMS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_GAMEOBJECT_CUSTOM_ANIM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_AREATRIGGER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAreaTriggerOpcode);
    OPCODE( MSG_MOVE_START_FORWARD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_START_BACKWARD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_STOP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_START_STRAFE_LEFT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_START_STRAFE_RIGHT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_STOP_STRAFE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_JUMP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_START_TURN_LEFT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_START_TURN_RIGHT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_STOP_TURN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_START_PITCH_UP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_START_PITCH_DOWN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_STOP_PITCH, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_SET_RUN_MODE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_SET_WALK_MODE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_TOGGLE_LOGGING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_TELEPORT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_TELEPORT_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_TELEPORT_ACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveTeleportAck);
    OPCODE( MSG_MOVE_TOGGLE_FALL_LOGGING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_FALL_LAND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_START_SWIM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_STOP_SWIM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_SET_RUN_SPEED_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_RUN_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_RUN_BACK_SPEED_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_RUN_BACK_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_WALK_SPEED_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_WALK_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_SWIM_SPEED_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_SWIM_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_SWIM_BACK_SPEED_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_SWIM_BACK_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_ALL_SPEED_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_TURN_RATE_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_TURN_RATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_TOGGLE_COLLISION_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_FACING, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_SET_PITCH, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_WORLDPORT_ACK, STATUS_TRANSFER, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveWorldportAckOpcode);
    OPCODE( SMSG_MONSTER_MOVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_WATER_WALK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_LAND_WALK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_MOVE_SET_RAW_POSITION_ACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_MOVE_SET_RAW_POSITION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_FORCE_RUN_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_RUN_SPEED_CHANGE_ACK, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleForceSpeedChangeAck);
    OPCODE( SMSG_FORCE_RUN_BACK_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleForceSpeedChangeAck);
    OPCODE( SMSG_FORCE_SWIM_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_SWIM_SPEED_CHANGE_ACK, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleForceSpeedChangeAck);
    OPCODE( SMSG_FORCE_MOVE_ROOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_MOVE_ROOT_ACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveRootAck);
    OPCODE( SMSG_FORCE_MOVE_UNROOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_MOVE_UNROOT_ACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveUnRootAck);
    OPCODE( MSG_MOVE_ROOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_UNROOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_HEARTBEAT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( SMSG_MOVE_KNOCK_BACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MOVE_KNOCK_BACK_ACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveKnockBackAck);
    OPCODE( MSG_MOVE_KNOCK_BACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_MOVE_FEATHER_FALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_NORMAL_FALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_SET_HOVER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_UNSET_HOVER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MOVE_HOVER_ACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveHoverAck);
    OPCODE( MSG_MOVE_HOVER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_TRIGGER_CINEMATIC_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_OPENING_CINEMATIC, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_TRIGGER_CINEMATIC, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_NEXT_CINEMATIC_CAMERA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleNextCinematicCamera);
    OPCODE( CMSG_COMPLETE_CINEMATIC, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCompleteCinematic);
    OPCODE( SMSG_TUTORIAL_FLAGS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TUTORIAL_FLAG, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTutorialFlag);
    OPCODE( CMSG_TUTORIAL_CLEAR, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTutorialClear);
    OPCODE( CMSG_TUTORIAL_RESET, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTutorialReset);
    OPCODE( CMSG_STANDSTATECHANGE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleStandStateChangeOpcode);
    OPCODE( CMSG_EMOTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleEmoteOpcode);
    OPCODE( SMSG_EMOTE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TEXT_EMOTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTextEmoteOpcode);
    OPCODE( SMSG_TEXT_EMOTE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_AUTOEQUIP_GROUND_ITEM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_AUTOSTORE_GROUND_ITEM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_AUTOSTORE_LOOT_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAutostoreLootItemOpcode);
    OPCODE( CMSG_AUTOSTORE_LOOT_CURRENCY,                 STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,  &WorldSession::HandleAutostoreLootItemOpcode   );
    OPCODE( CMSG_STORE_LOOT_IN_SLOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_AUTOEQUIP_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAutoEquipItemOpcode);
    OPCODE( CMSG_AUTOSTORE_BAG_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAutoStoreBagItemOpcode);
    OPCODE( CMSG_SWAP_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSwapItem);
    OPCODE( CMSG_SWAP_INV_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSwapInvItemOpcode);
    OPCODE( CMSG_SPLIT_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSplitItemOpcode);
    OPCODE( CMSG_AUTOEQUIP_ITEM_SLOT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAutoEquipItemSlotOpcode);
    OPCODE( OBSOLETE_DROP_ITEM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_DESTROYITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleDestroyItemOpcode);
    OPCODE( SMSG_INVENTORY_CHANGE_FAILURE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_OPEN_CONTAINER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_INSPECT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleInspectOpcode);
    OPCODE( SMSG_INSPECT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_INITIATE_TRADE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleInitiateTradeOpcode);
    OPCODE( CMSG_BEGIN_TRADE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBeginTradeOpcode);
    OPCODE( CMSG_BUSY_TRADE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBusyTradeOpcode);
    OPCODE( CMSG_IGNORE_TRADE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleIgnoreTradeOpcode);
    OPCODE( CMSG_ACCEPT_TRADE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAcceptTradeOpcode);
    OPCODE( CMSG_UNACCEPT_TRADE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleUnacceptTradeOpcode);
    OPCODE( CMSG_CANCEL_TRADE, STATUS_LOGGEDIN_OR_RECENTLY_LOGGOUT,
            PROCESS_THREADUNSAFE, &WorldSession::HandleCancelTradeOpcode);
    OPCODE( CMSG_SET_TRADE_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetTradeItemOpcode);
    OPCODE( CMSG_CLEAR_TRADE_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleClearTradeItemOpcode);
    OPCODE( CMSG_SET_TRADE_GOLD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetTradeGoldOpcode);
    OPCODE( SMSG_TRADE_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_TRADE_STATUS_EXTENDED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_INITIALIZE_FACTIONS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SET_FACTION_VISIBLE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SET_FACTION_STANDING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_FACTION_ATWAR, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetFactionAtWar);
    OPCODE( CMSG_SET_FACTION_CHEAT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetFactionCheat);
    OPCODE( SMSG_SET_PROFICIENCY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_ACTION_BUTTON, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetActionButtonOpcode);
    OPCODE( SMSG_ACTION_BUTTONS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_INITIAL_SPELLS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LEARNED_SPELL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SUPERCEDED_SPELL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_NEW_SPELL_SLOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CAST_SPELL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCastSpellOpcode);
    OPCODE( CMSG_CANCEL_CAST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCancelCastOpcode);
    OPCODE( SMSG_CAST_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_START, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_GO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_FAILURE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_COOLDOWN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_COOLDOWN_EVENT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CANCEL_AURA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCancelAuraOpcode);
    OPCODE( SMSG_EQUIPMENT_SET_SAVED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_CAST_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_CHANNEL_START, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_CHANNEL_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CANCEL_CHANNELLING, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCancelChanneling);
    OPCODE( SMSG_AI_REACTION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_SELECTION, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetSelectionOpcode);
    OPCODE( CMSG_EQUIPMENT_SET_DELETE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleEquipmentSetDelete);
    OPCODE( CMSG_INSTANCE_LOCK_WARNING_RESPONSE, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleInstanceLockResponse);
    OPCODE( CMSG_UNUSED2, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_ATTACKSWING, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAttackSwingOpcode);
    OPCODE( CMSG_ATTACKSTOP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAttackStopOpcode);
    OPCODE( SMSG_ATTACKSTART, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ATTACKSTOP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ATTACKSWING_NOTINRANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ATTACKSWING_BADFACING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_INSTANCE_LOCK_WARNING_QUERY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ATTACKSWING_DEADTARGET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ATTACKSWING_CANT_ATTACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ATTACKERSTATEUPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEFIELD_PORT_DENIED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DAMAGE_DONE_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_UNIT_SPELLCAST_START, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CANCEL_COMBAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELLBREAKLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELLHEALLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELLENERGIZELOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BREAK_TARGET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SAVE_PLAYER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SETDEATHBINDPOINT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_BINDPOINTUPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GETDEATHBINDZONE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_BINDZONEREPLY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PLAYERBOUND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CLIENT_CONTROL_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REPOP_REQUEST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRepopRequestOpcode);
    OPCODE( SMSG_RESURRECT_REQUEST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_RESURRECT_RESPONSE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleResurrectResponseOpcode);
    OPCODE( CMSG_LOOT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLootOpcode);
    OPCODE( CMSG_LOOT_MONEY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLootMoneyOpcode);
    OPCODE( CMSG_LOOT_RELEASE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLootReleaseOpcode);
    OPCODE( SMSG_LOOT_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_RELEASE_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_REMOVED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_MONEY_NOTIFY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_ITEM_NOTIFY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_CLEAR_MONEY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ITEM_PUSH_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DUEL_REQUESTED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DUEL_OUTOFBOUNDS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DUEL_INBOUNDS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DUEL_COMPLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DUEL_WINNER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_DUEL_ACCEPTED, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleDuelAcceptedOpcode);
    OPCODE( CMSG_DUEL_CANCELLED, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleDuelCancelledOpcode);
    OPCODE( SMSG_MOUNTRESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DISMOUNTRESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PUREMOUNT_CANCELLED_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MOUNTSPECIAL_ANIM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMountSpecialAnimOpcode);
    OPCODE( SMSG_MOUNTSPECIAL_ANIM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_TAME_FAILURE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PET_SET_ACTION, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetSetAction);
    OPCODE( CMSG_PET_ACTION, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetAction);
    OPCODE( CMSG_PET_ABANDON, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetAbandon);
    OPCODE( CMSG_PET_RENAME, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetRename);
    OPCODE( SMSG_PET_NAME_INVALID, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_SPELLS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_MODE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GOSSIP_HELLO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGossipHelloOpcode);
    OPCODE( CMSG_GOSSIP_SELECT_OPTION, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGossipSelectOptionOpcode);
    OPCODE( SMSG_GOSSIP_MESSAGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GOSSIP_COMPLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_NPC_TEXT_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleNpcTextQueryOpcode);
    OPCODE( SMSG_NPC_TEXT_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_NPC_WONT_TALK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUESTGIVER_STATUS_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverStatusQueryOpcode);
    OPCODE( SMSG_QUESTGIVER_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUESTGIVER_HELLO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverHelloOpcode);
    OPCODE( SMSG_QUESTGIVER_QUEST_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUESTGIVER_QUERY_QUEST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverQueryQuestOpcode);
    OPCODE( CMSG_QUESTGIVER_QUEST_AUTOLAUNCH, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverQuestAutoLaunch);
    OPCODE( SMSG_QUESTGIVER_QUEST_DETAILS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUESTGIVER_ACCEPT_QUEST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverAcceptQuestOpcode);
    OPCODE( CMSG_QUESTGIVER_COMPLETE_QUEST, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleQuestgiverCompleteQuest);
    OPCODE( SMSG_QUESTGIVER_REQUEST_ITEMS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUESTGIVER_REQUEST_REWARD, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverRequestRewardOpcode);
    OPCODE( SMSG_QUESTGIVER_OFFER_REWARD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUESTGIVER_CHOOSE_REWARD, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverChooseRewardOpcode);
    OPCODE( SMSG_QUESTGIVER_QUEST_INVALID, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUESTGIVER_CANCEL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverCancel);
    OPCODE( SMSG_QUESTGIVER_QUEST_COMPLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_QUESTGIVER_QUEST_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUESTLOG_SWAP_QUEST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestLogSwapQuest);
    OPCODE( CMSG_QUESTLOG_REMOVE_QUEST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestLogRemoveQuest);
    OPCODE( SMSG_QUESTLOG_FULL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_QUESTUPDATE_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_QUESTUPDATE_FAILEDTIMER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_QUESTUPDATE_COMPLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_QUESTUPDATE_ADD_KILL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_QUESTUPDATE_ADD_ITEM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUEST_CONFIRM_ACCEPT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestConfirmAccept);
    OPCODE( SMSG_QUEST_CONFIRM_ACCEPT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PUSHQUESTTOPARTY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePushQuestToParty);
    OPCODE( CMSG_LIST_INVENTORY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleListInventoryOpcode);
    OPCODE( SMSG_LIST_INVENTORY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SELL_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSellItemOpcode);
    OPCODE( SMSG_SELL_ITEM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BUY_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBuyItemInSlotOpcode);
    OPCODE( SMSG_BUY_ITEM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BUY_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TAXICLEARALLNODES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_TAXIENABLEALLNODES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_TAXISHOWNODES, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTaxiQueryAvailableNodes);
    OPCODE( SMSG_SHOWTAXINODES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TAXINODE_STATUS_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTaxiNodeStatusQueryOpcode);
    OPCODE( SMSG_TAXINODE_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TAXIQUERYAVAILABLENODES, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTaxiQueryAvailableNodes);
    OPCODE( CMSG_ACTIVATETAXI, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleActivateTaxiOpcode);
    OPCODE( SMSG_ACTIVATETAXIREPLY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_NEW_TAXI_PATH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TRAINER_LIST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTrainerListOpcode);
    OPCODE( SMSG_TRAINER_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TRAINER_BUY_SPELL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTrainerBuySpellOpcode);
    OPCODE( SMSG_TRAINER_BUY_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BINDER_ACTIVATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBinderActivateOpcode);
    OPCODE( SMSG_PLAYERBINDERROR, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BANKER_ACTIVATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBankerActivateOpcode);
    OPCODE( SMSG_SHOW_BANK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BUY_BANK_SLOT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBuyBankSlotOpcode);
    OPCODE( SMSG_BUY_BANK_SLOT_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PETITION_SHOWLIST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetitionShowListOpcode);
    OPCODE( SMSG_PETITION_SHOWLIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PETITION_BUY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetitionBuyOpcode);
    OPCODE( CMSG_PETITION_SHOW_SIGNATURES, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandlePetitionShowSignOpcode);
    OPCODE( SMSG_PETITION_SHOW_SIGNATURES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PETITION_SIGN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetitionSignOpcode);
    OPCODE( SMSG_PETITION_SIGN_RESULTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_PETITION_DECLINE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetitionDeclineOpcode);
    OPCODE( CMSG_OFFER_PETITION, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleOfferPetitionOpcode);
    OPCODE( CMSG_TURN_IN_PETITION, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTurnInPetitionOpcode);
    OPCODE( SMSG_TURN_IN_PETITION_RESULTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PETITION_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetitionQueryOpcode);
    OPCODE( SMSG_PETITION_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_FISH_NOT_HOOKED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_FISH_ESCAPED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BUG, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBugOpcode);
    OPCODE( SMSG_NOTIFICATION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PLAYED_TIME, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePlayedTime);
    OPCODE( SMSG_PLAYED_TIME, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUERY_TIME, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQueryTimeOpcode);
    OPCODE( SMSG_QUERY_TIME_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOG_XPGAIN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AURACASTLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_RECLAIM_CORPSE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleReclaimCorpseOpcode);
    OPCODE( CMSG_WRAP_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleWrapItemOpcode);
    OPCODE( SMSG_LEVELUP_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_MINIMAP_PING, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMinimapPingOpcode);
    OPCODE( SMSG_RESISTLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ENCHANTMENTLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_SKILL_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_START_MIRROR_TIMER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PAUSE_MIRROR_TIMER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_STOP_MIRROR_TIMER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_EarlyProccess);
    OPCODE( SMSG_PONG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CLEAR_COOLDOWN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GAMEOBJECT_PAGETEXT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SETSHEATHED, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetSheathedOpcode);
    OPCODE( SMSG_COOLDOWN_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_DELAYED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUEST_POI_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestPOIQuery);
    OPCODE( SMSG_QUEST_POI_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GHOST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GM_INVIS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_INVALID_PROMOTION_CODE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_GM_BIND_OTHER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_GM_SUMMON, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_ITEM_TIME_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ITEM_ENCHANT_TIME_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AUTH_CHALLENGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_AUTH_SESSION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_EarlyProccess);
    OPCODE( SMSG_AUTH_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_GM_SHOWLABEL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_PET_CAST_SPELL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetCastSpellOpcode);
    OPCODE( MSG_SAVE_GUILD_EMBLEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSaveGuildEmblemOpcode);
    OPCODE( MSG_TABARDVENDOR_ACTIVATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTabardVendorActivateOpcode);
    OPCODE( SMSG_PLAY_SPELL_VISUAL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ZONEUPDATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleZoneUpdateOpcode);
    OPCODE( SMSG_PARTYKILLLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_COMPRESSED_UPDATE_OBJECT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PLAY_SPELL_IMPACT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_EXPLORATION_EXPERIENCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_SET_SECURITY_GROUP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GM_NUKE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_RANDOM_ROLL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRandomRollOpcode);
    OPCODE( SMSG_ENVIRONMENTALDAMAGELOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PLAYER_DIFFICULTY_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_RWHOIS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_PLAYER_REWARD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_TELEPORT_DENIED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_UNLEARN_SPELL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_UNLEARN_SKILL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleUnlearnSkillOpcode);
    OPCODE( SMSG_REMOVED_SPELL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_DECHARGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GMTICKET_CREATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGMTicketCreateOpcode);
    OPCODE( SMSG_GMTICKET_CREATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GMTICKET_UPDATETEXT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGMTicketUpdateOpcode);
    OPCODE( SMSG_GMTICKET_UPDATETEXT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ACCOUNT_DATA_TIMES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REQUEST_ACCOUNT_DATA, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRequestAccountData);
    OPCODE( CMSG_UPDATE_ACCOUNT_DATA, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleUpdateAccountData);
    OPCODE( SMSG_UPDATE_ACCOUNT_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CLEAR_FAR_SIGHT_IMMEDIATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PLAYER_DIFFICULTY_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_TEACH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GM_CREATE_ITEM_TARGET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GMTICKET_GETTICKET, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGMTicketGetTicketOpcode);
    OPCODE( SMSG_GMTICKET_GETTICKET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_UNLEARN_TALENTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_UPDATE_INSTANCE_ENCOUNTER_UNIT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GAMEOBJECT_DESPAWN_ANIM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_CORPSE_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCorpseQueryOpcode);
    OPCODE( CMSG_GMTICKET_DELETETICKET, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGMTicketDeleteOpcode);
    OPCODE( SMSG_GMTICKET_DELETETICKET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CHAT_WRONG_FACTION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GMTICKET_SYSTEMSTATUS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGMTicketSystemStatusOpcode);
    OPCODE( SMSG_GMTICKET_SYSTEMSTATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SPIRIT_HEALER_ACTIVATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSpiritHealerActivateOpcode);
    OPCODE( SMSG_QUEST_FORCE_REMOVED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SKILL_BUY_STEP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SKILL_BUY_RANK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SPIRIT_HEALER_CONFIRM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHARACTER_POINT_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_GOSSIP_POI, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHAT_IGNORED, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChatIgnoredOpcode);
    OPCODE( CMSG_GUILD_RANK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildRankOpcode);
    OPCODE( CMSG_GUILD_ADD_RANK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildAddRankOpcode);
    OPCODE( CMSG_GUILD_DEL_RANK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildDelRankOpcode);
    OPCODE( CMSG_GUILD_SWITCH_RANK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GUILD_SET_NOTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildSetNoteOpcode);
    OPCODE( SMSG_LOGIN_VERIFY_WORLD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CLEAR_EXPLORATION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SEND_MAIL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSendMail);
    OPCODE( SMSG_SEND_MAIL_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GET_MAIL_LIST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGetMailList);
    OPCODE( SMSG_MAIL_LIST_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEFIELD_LIST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBattlefieldListOpcode);
    OPCODE( SMSG_BATTLEFIELD_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEFIELD_JOIN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBattlemasterJoinOpcode);
    OPCODE( CMSG_REQUEST_RATED_BG_INFO, STATUS_NEVER, PROCESS_THREADUNSAFE,
        &WorldSession::Handle_NULL);
    OPCODE( CMSG_REQUEST_PVP_OPTIONS_ENABLED, STATUS_NEVER, PROCESS_THREADUNSAFE,
        &WorldSession::Handle_NULL);
    OPCODE( CMSG_TAXICLEARNODE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_TAXIENABLENODE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_ITEM_TEXT_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleItemTextQuery);
    OPCODE( SMSG_ITEM_TEXT_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MAIL_TAKE_MONEY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMailTakeMoney);
    OPCODE( CMSG_MAIL_TAKE_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMailTakeItem);
    OPCODE( CMSG_MAIL_MARK_AS_READ, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMailMarkAsRead);
    OPCODE( CMSG_MAIL_RETURN_TO_SENDER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMailReturnToSender);
    OPCODE( CMSG_MAIL_DELETE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMailDelete);
    OPCODE( CMSG_MAIL_CREATE_TEXT_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMailCreateTextItem);
    OPCODE( SMSG_SPELLLOGMISS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELLLOGEXECUTE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DEBUGAURAPROC, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PERIODICAURALOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELLDAMAGESHIELD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELLNONMELEEDAMAGELOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LEARN_TALENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLearnTalentOpcode);
    OPCODE( SMSG_RESURRECT_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TOGGLE_PVP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTogglePvP);
    OPCODE( SMSG_ZONE_UNDER_ATTACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_AUCTION_HELLO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAuctionHelloOpcode);
    OPCODE( CMSG_AUCTION_SELL_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAuctionSellItem);
    OPCODE( CMSG_AUCTION_REMOVE_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAuctionRemoveItem);
    OPCODE( CMSG_AUCTION_LIST_ITEMS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAuctionListItems);
    OPCODE( CMSG_AUCTION_LIST_OWNER_ITEMS, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionListOwnerItems);
    OPCODE( CMSG_AUCTION_PLACE_BID, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAuctionPlaceBid);
    OPCODE( SMSG_AUCTION_COMMAND_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AUCTION_LIST_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AUCTION_OWNER_LIST_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AUCTION_BIDDER_NOTIFICATION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AUCTION_OWNER_NOTIFICATION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PROCRESIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_STANDSTATE_CHANGE_FAILURE_OBSOLETE, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DISPEL_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELLORDAMAGE_IMMUNE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_AUCTION_LIST_BIDDER_ITEMS, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionListBidderItems);
    OPCODE( SMSG_AUCTION_BIDDER_LIST_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SET_FLAT_SPELL_MODIFIER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SET_PCT_SPELL_MODIFIER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_AMMO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetAmmoOpcode);
    OPCODE( SMSG_CORPSE_RECLAIM_DELAY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_ACTIVE_MOVER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetActiveMoverOpcode);
    OPCODE( CMSG_PET_CANCEL_AURA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetCancelAuraOpcode);
    OPCODE( CMSG_PLAYER_AI_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CANCEL_AUTO_REPEAT_SPELL, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleCancelAutoRepeatSpellOpcode);
    OPCODE( MSG_GM_ACCOUNT_ONLINE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_LIST_STABLED_PETS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleListStabledPetsOpcode);
    OPCODE( SMSG_STABLE_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_STABLE_REVIVE_PET, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleStableRevivePet);
    OPCODE( CMSG_STABLE_CHANGE_SLOT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleStableChangeSlot);
    OPCODE( MSG_QUEST_PUSH_RESULT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestPushResult);
    OPCODE( SMSG_PLAY_MUSIC, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PLAY_OBJECT_SOUND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REQUEST_PET_INFO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRequestPetInfoOpcode);
    OPCODE( CMSG_FAR_SIGHT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleFarSightOpcode);
    OPCODE( SMSG_SPELLDISPELLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DAMAGE_CALC_LOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ENABLE_DAMAGE_LOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GROUP_CHANGE_SUB_GROUP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupChangeSubGroupOpcode);
    OPCODE( CMSG_REQUEST_PARTY_MEMBER_STATS, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleRequestPartyMemberStatsOpcode);
    OPCODE( CMSG_GROUP_SWAP_SUB_GROUP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_RESET_FACTION_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_AUTOSTORE_BANK_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAutoStoreBankItemOpcode);
    OPCODE( CMSG_AUTOBANK_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAutoBankItemOpcode);
    OPCODE( MSG_QUERY_NEXT_MAIL_TIME, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQueryNextMailTime);
    OPCODE( SMSG_RECEIVED_MAIL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_RAID_GROUP_ONLY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_DURABILITY_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_PVP_RANK_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_ADD_PVP_MEDAL_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_DEL_PVP_MEDAL_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_PVP_TITLE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_PVP_CREDIT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AUCTION_REMOVED_NOTIFICATION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GROUP_RAID_CONVERT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupRaidConvertOpcode);
    OPCODE( CMSG_GROUP_ASSISTANT_LEADER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGroupAssistantLeaderOpcode);
    OPCODE( CMSG_BUYBACK_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBuybackItem);
    OPCODE( SMSG_SERVER_MESSAGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_SAVED_INSTANCE_EXTEND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_LFG_OFFER_CONTINUE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MEETINGSTONE_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_MEETINGSTONE_SETQUEUE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MEETINGSTONE_INFO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMeetingStoneInfo);
    OPCODE( SMSG_MEETINGSTONE_COMPLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MEETINGSTONE_IN_PROGRESS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MEETINGSTONE_MEMBER_ADDED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GMTICKETSYSTEM_TOGGLE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CANCEL_GROWTH_AURA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCancelGrowthAuraOpcode);
    OPCODE( SMSG_CANCEL_AUTO_REPEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_STANDSTATE_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_ALL_PASSED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_ROLL_WON, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LOOT_ROLL, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLootRoll);
    OPCODE( SMSG_LOOT_START_ROLL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_ROLL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LOOT_MASTER_GIVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLootMasterGiveOpcode);
    OPCODE( SMSG_LOOT_MASTER_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SET_FORCED_REACTIONS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_FAILED_OTHER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GAMEOBJECT_RESET_STATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REPAIR_ITEM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRepairItemOpcode);
    OPCODE( SMSG_CHAT_PLAYER_NOT_FOUND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_TALENT_WIPE_CONFIRM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTalentWipeConfirmOpcode);
    OPCODE( SMSG_SUMMON_REQUEST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SUMMON_RESPONSE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSummonResponseOpcode);
    OPCODE( MSG_MOVE_TOGGLE_GRAVITY_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_MONSTER_MOVE_TRANSPORT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_BROKEN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_MOVE_FEATHER_FALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_WATER_WALK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SERVER_BROADCAST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SELF_RES, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSelfResOpcode);
    OPCODE( SMSG_FEIGN_DEATH_RESISTED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_RUN_SCRIPT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SCRIPT_MESSAGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DUEL_COUNTDOWN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AREA_TRIGGER_MESSAGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SHOWING_HELM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleShowingHelmOpcode);
    OPCODE( CMSG_SHOWING_CLOAK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleShowingCloakOpcode);
    OPCODE( SMSG_LFG_ROLE_CHOSEN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PLAYER_SKINNED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DURABILITY_DAMAGE_DEATH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_EXPLORATION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_ACTIONBAR_TOGGLES, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetActionBarToggles);
    OPCODE( MSG_PETITION_RENAME, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetitionRenameOpcode);
    OPCODE( SMSG_INIT_WORLD_STATES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_UPDATE_WORLD_STATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ITEM_NAME_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleItemNameQueryOpcode);
    OPCODE( SMSG_ITEM_NAME_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_ACTION_FEEDBACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHAR_RENAME, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCharRenameOpcode);
    OPCODE( SMSG_CHAR_RENAME, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MOVE_SPLINE_DONE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveSplineDoneOpcode);
    OPCODE( CMSG_MOVE_FALL_RESET, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( SMSG_INSTANCE_SAVE_CREATED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_RAID_INSTANCE_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REQUEST_RAID_INFO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRequestRaidInfoOpcode);
    OPCODE( CMSG_MOVE_TIME_SKIPPED, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveTimeSkippedOpcode);
    OPCODE( CMSG_MOVE_FEATHER_FALL_ACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleFeatherFallAck);
    OPCODE( CMSG_MOVE_WATER_WALK_ACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveWaterWalkAck);
    OPCODE( CMSG_MOVE_NOT_ACTIVE_MOVER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveNotActiveMover);
    OPCODE( SMSG_PLAY_SOUND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEFIELD_STATUS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBattlefieldStatusOpcode);
    OPCODE( SMSG_BATTLEFIELD_STATUS1, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEFIELD_STATUS2, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEFIELD_STATUS3, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEFIELD_STATUS4, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEFIELD_PORT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBattleFieldPortOpcode);
    OPCODE( CMSG_INSPECT_HONOR_STATS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleInspectHonorStatsOpcode);
    OPCODE( SMSG_INSPECT_HONOR_STATS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEMASTER_HELLO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBattlemasterHelloOpcode);
    OPCODE( CMSG_MOVE_START_SWIM_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_MOVE_STOP_SWIM_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_FORCE_WALK_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_WALK_SPEED_CHANGE_ACK, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleForceSpeedChangeAck);
    OPCODE( SMSG_FORCE_SWIM_BACK_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_SWIM_BACK_SPEED_CHANGE_ACK, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleForceSpeedChangeAck);
    OPCODE( SMSG_FORCE_TURN_RATE_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_TURN_RATE_CHANGE_ACK, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleForceSpeedChangeAck);
    OPCODE( MSG_PVP_LOG_DATA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePVPLogDataOpcode);
    OPCODE( CMSG_BATTLEFIELD_REQUEST_SCORE_DATA, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandlePVPLogDataOpcode);
    OPCODE( CMSG_LEAVE_BATTLEFIELD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLeaveBattlefieldOpcode);
    OPCODE( CMSG_AREA_SPIRIT_HEALER_QUERY, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleAreaSpiritHealerQueryOpcode);
    OPCODE( CMSG_AREA_SPIRIT_HEALER_QUEUE, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleAreaSpiritHealerQueueOpcode);
    OPCODE( SMSG_AREA_SPIRIT_HEALER_TIME, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_UNTEACH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_WARDEN_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_WARDEN_DATA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleWardenDataOpcode);
    OPCODE( SMSG_GROUP_JOINED_BATTLEGROUND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEGROUND_PLAYER_POSITIONS, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleBattlegroundPlayerPositionsOpcode);
    OPCODE( SMSG_BATTLEGROUND_PLAYER_POSITIONS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PET_STOP_ATTACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetStopAttack);
    OPCODE( SMSG_BINDER_CONFIRM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEGROUND_PLAYER_JOINED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEGROUND_PLAYER_LEFT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ADDON_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PET_UNLEARN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_PET_UNLEARN_CONFIRM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PARTY_MEMBER_STATS_FULL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PET_SPELL_AUTOCAST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetSpellAutocastOpcode);
    OPCODE( SMSG_WEATHER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PLAY_TIME_WARNING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MINIGAME_SETUP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MINIGAME_STATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MINIGAME_MOVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_MINIGAME_MOVE_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_RAID_INSTANCE_MESSAGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_COMPRESSED_MOVES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GUILD_INFO_TEXT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildChangeInfoTextOpcode);
    OPCODE( SMSG_CHAT_RESTRICTED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_SET_RUN_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_SET_RUN_BACK_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_SET_SWIM_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_SET_WALK_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_SET_SWIM_BACK_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_SET_TURN_RATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_UNROOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_FEATHER_FALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_NORMAL_FALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_SET_HOVER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_UNSET_HOVER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_WATER_WALK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_LAND_WALK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_START_SWIM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_STOP_SWIM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_SET_RUN_MODE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_SET_WALK_MODE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_NUKE_ACCOUNT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_GM_DESTROY_CORPSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GM_DESTROY_ONLINE_CORPSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_ACTIVATETAXIEXPRESS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleActivateTaxiExpressOpcode);
    OPCODE( SMSG_SET_FACTION_ATWAR, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GAMETIMEBIAS_SET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_DEBUG_ACTIONS_START, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_DEBUG_ACTIONS_STOP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_FACTION_INACTIVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetFactionInactiveOpcode);
    OPCODE( CMSG_SET_WATCHED_FACTION, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetWatchedFactionOpcode);
    OPCODE( MSG_MOVE_TIME_SKIPPED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SPLINE_MOVE_ROOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_EXPLORATION_ALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_INVALIDATE_PLAYER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_RESET_INSTANCES, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleResetInstancesOpcode);
    OPCODE( SMSG_INSTANCE_RESET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_INSTANCE_RESET_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_UPDATE_LAST_INSTANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_RAID_TARGET_UPDATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRaidTargetUpdateOpcode);
    OPCODE( MSG_RAID_READY_CHECK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRaidReadyCheckOpcode);
    OPCODE( CMSG_LUA_USAGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_PET_ACTION_SOUND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_DISMISS_SOUND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GHOSTEE_GONE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_UPDATE_TICKET_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_GM_TICKET_STATUS_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_SET_DUNGEON_DIFFICULTY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetDungeonDifficultyOpcode);
    OPCODE( CMSG_GMSURVEY_SUBMIT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGMSurveySubmit);
    OPCODE( SMSG_UPDATE_INSTANCE_OWNERSHIP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_IGNORE_KNOCKBACK_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CHAT_PLAYER_AMBIGUOUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_DELAY_GHOST_TELEPORT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SPELLINSTAKILLLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_UPDATE_CHAIN_TARGETS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHAT_FILTERED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_EXPECTED_SPAM_RECORDS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELLSTEALLOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LOTTERY_QUERY_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_LOTTERY_QUERY_RESULT_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BUY_LOTTERY_TICKET_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_LOTTERY_RESULT_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CHARACTER_PROFILE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CHARACTER_PROFILE_REALM_CONNECTED, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DEFENSE_MESSAGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_INSTANCE_DIFFICULTY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_GM_RESETINSTANCELIMIT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_MOTD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_SET_FLIGHT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_UNSET_FLIGHT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MOVE_FLIGHT_ACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_START_SWIM_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_STOP_SWIM_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_MOVE_SET_CAN_FLY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_UNSET_CAN_FLY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MOVE_SET_CAN_FLY_ACK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMoveSetCanFlyAckOpcode);
    OPCODE( CMSG_MOVE_SET_FLY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( CMSG_SOCKET_GEMS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSocketOpcode);
    OPCODE( CMSG_ARENA_TEAM_CREATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamCreate);
    OPCODE( SMSG_ARENA_TEAM_COMMAND_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ARENA_TEAM_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamQueryOpcode);
    OPCODE( SMSG_ARENA_TEAM_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ARENA_TEAM_ROSTER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamRosterOpcode);
    OPCODE( SMSG_ARENA_TEAM_ROSTER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ARENA_TEAM_INVITE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamInviteOpcode);
    OPCODE( SMSG_ARENA_TEAM_INVITE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ARENA_TEAM_ACCEPT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamAcceptOpcode);
    OPCODE( CMSG_ARENA_TEAM_DECLINE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamDeclineOpcode);
    OPCODE( CMSG_ARENA_TEAM_LEAVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamLeaveOpcode);
    OPCODE( CMSG_ARENA_TEAM_REMOVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamRemoveOpcode);
    OPCODE( CMSG_ARENA_TEAM_DISBAND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamDisbandOpcode);
    OPCODE( CMSG_ARENA_TEAM_LEADER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleArenaTeamLeaderOpcode);
    OPCODE( SMSG_ARENA_TEAM_EVENT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEMASTER_JOIN_ARENA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleBattlemasterJoinArena);
    OPCODE( MSG_MOVE_START_ASCEND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_MOVE_STOP_ASCEND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( SMSG_ARENA_TEAM_STATS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LFG_JOIN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgJoinOpcode);
    OPCODE( CMSG_LFG_LEAVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgLeaveOpcode);
    OPCODE( CMSG_SEARCH_LFG_JOIN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfrSearchOpcode);
    OPCODE( CMSG_SEARCH_LFG_LEAVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfrLeaveOpcode);
    OPCODE( SMSG_UPDATE_LFG_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_PROPOSAL_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LFG_PROPOSAL_RESULT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgProposalResultOpcode);
    OPCODE( SMSG_LFG_ROLE_CHECK_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_JOIN_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_QUEUE_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_LFG_COMMENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgSetCommentOpcode);
    OPCODE( SMSG_LFG_UPDATE_PLAYER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_UPDATE_PARTY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_UPDATE_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LFG_SET_ROLES, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgSetRolesOpcode);
    OPCODE( CMSG_LFG_SET_NEEDS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_LFG_SET_BOOT_VOTE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgSetBootVoteOpcode);
    OPCODE( SMSG_LFG_BOOT_PROPOSAL_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LFD_PLAYER_LOCK_INFO_REQUEST, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgPlayerLockInfoRequestOpcode);
    OPCODE( SMSG_LFG_PLAYER_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LFG_TELEPORT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgTeleportOpcode);
    OPCODE( CMSG_LFD_PARTY_LOCK_INFO_REQUEST, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleLfgPartyLockInfoRequestOpcode);
    OPCODE( SMSG_LFG_PARTY_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_TITLE_EARNED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_TITLE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetTitleOpcode);
    OPCODE( CMSG_CANCEL_MOUNT_AURA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCancelMountAuraOpcode);
    OPCODE( SMSG_ARENA_ERROR, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_INSPECT_ARENA_TEAMS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleInspectArenaTeamsOpcode);
    OPCODE( SMSG_DEATH_RELEASE_LOC, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CANCEL_TEMP_ENCHANTMENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCancelTempEnchantmentOpcode);
    OPCODE( SMSG_FORCED_DEATH_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHEAT_SET_HONOR_CURRENCY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHEAT_SET_ARENA_CURRENCY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_FLIGHT_SPEED_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_FLIGHT_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_FLIGHT_BACK_SPEED_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_FLIGHT_BACK_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_FORCE_FLIGHT_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_FLIGHT_SPEED_CHANGE_ACK, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleForceSpeedChangeAck);
    OPCODE( SMSG_FORCE_FLIGHT_BACK_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleForceSpeedChangeAck);
    OPCODE( SMSG_SPLINE_SET_FLIGHT_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_SET_FLIGHT_BACK_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MAELSTROM_INVALIDATE_CACHE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_FLIGHT_SPLINE_SYNC, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_TAXI_BENCHMARK_MODE, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetTaxiBenchmarkOpcode);
    OPCODE( SMSG_JOINED_BATTLEGROUND_QUEUE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_REALM_SPLIT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REALM_SPLIT, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRealmSplitOpcode);
    OPCODE( CMSG_MOVE_CHNG_TRANSPORT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( MSG_PARTY_ASSIGNMENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePartyAssignmentOpcode);
    OPCODE( SMSG_OFFER_PETITION_ERROR, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_TIME_SYNC_REQ, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TIME_SYNC_RESP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTimeSyncResp);
    OPCODE( CMSG_SEND_LOCAL_EVENT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SEND_GENERAL_TRIGGER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SEND_COMBAT_TRIGGER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_MAELSTROM_GM_SENT_MAIL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_RESET_FAILED_NOTIFY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_REAL_GROUP_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_DISABLED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ACTIVE_PVP_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHEAT_DUMP_ITEMS_DEBUG_ONLY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CHEAT_DUMP_ITEMS_DEBUG_ONLY_RESPONSE, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CHEAT_DUMP_ITEMS_DEBUG_ONLY_RESPONSE_WRITE_FILE, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_UPDATE_COMBO_POINTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_VOICE_SESSION_ROSTER_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_VOICE_SESSION_LEAVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_VOICE_SESSION_ADJUST_PRIORITY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_VOICE_SET_TALKER_MUTED_REQUEST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_VOICE_SET_TALKER_MUTED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_INIT_EXTRA_AURA_INFO_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SET_EXTRA_AURA_INFO_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SET_EXTRA_AURA_INFO_NEED_UPDATE_OBSOLETE, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CLEAR_EXTRA_AURA_INFO_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_MOVE_START_DESCEND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMovementOpcodes);
    OPCODE( CMSG_IGNORE_REQUIREMENTS_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_IGNORE_REQUIREMENTS_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_CHANCE_PROC_LOG, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_MOVE_SET_RUN_SPEED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_DISMOUNT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_MOVE_UPDATE_CAN_FLY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_RAID_READY_CHECK_CONFIRM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_VOICE_SESSION_ENABLE, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleVoiceSessionEnableOpcode);
    OPCODE( SMSG_VOICE_SESSION_ENABLE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_VOICE_PARENTAL_CONTROLS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_WHISPER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_GM_MESSAGECHAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_GM_GEARRATING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_COMMENTATOR_ENABLE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_COMMENTATOR_STATE_CHANGED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_COMMENTATOR_GET_MAP_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_COMMENTATOR_MAP_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_COMMENTATOR_GET_PLAYER_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_COMMENTATOR_GET_PLAYER_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_COMMENTATOR_PLAYER_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_COMMENTATOR_ENTER_INSTANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_COMMENTATOR_EXIT_INSTANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_COMMENTATOR_INSTANCE_COMMAND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CLEAR_TARGET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BOT_DETECTED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CROSSED_INEBRIATION_THRESHOLD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHEAT_PLAYER_LOGIN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHEAT_PLAYER_LOOKUP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CHEAT_PLAYER_LOOKUP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_KICK_REASON, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_RAID_READY_CHECK_FINISHED, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleRaidReadyCheckFinishedOpcode);
    OPCODE( CMSG_COMPLAIN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleComplainOpcode);
    OPCODE( SMSG_COMPLAIN_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_FEATURE_SYSTEM_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_SHOW_COMPLAINTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GM_UNSQUELCH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHANNEL_SILENCE_VOICE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHANNEL_SILENCE_ALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHANNEL_UNSILENCE_VOICE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHANNEL_UNSILENCE_ALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_TARGET_CAST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_TARGET_SCRIPT_CAST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHANNEL_DISPLAY_LIST, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelDisplayListQuery);
    OPCODE( CMSG_SET_ACTIVE_VOICE_CHANNEL, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetActiveVoiceChannel);
    OPCODE( CMSG_GET_CHANNEL_MEMBER_COUNT, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleGetChannelMemberCount);
    OPCODE( SMSG_CHANNEL_MEMBER_COUNT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHANNEL_VOICE_ON, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelVoiceOnOpcode);
    OPCODE( CMSG_CHANNEL_VOICE_OFF, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_DEBUG_LIST_TARGETS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_DEBUG_LIST_TARGETS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AVAILABLE_VOICE_CHANNEL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ADD_VOICE_IGNORE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_DEL_VOICE_IGNORE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_PARTY_SILENCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_PARTY_UNSILENCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_NOTIFY_PARTY_SQUELCH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_COMSAT_RECONNECT_TRY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_COMSAT_DISCONNECT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_COMSAT_CONNECT_FAIL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_VOICE_CHAT_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REPORT_PVP_AFK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleReportPvPAFK);
    OPCODE( SMSG_REPORT_PVP_AFK_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GUILD_BANKER_ACTIVATE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildBankerActivate);
    OPCODE( CMSG_GUILD_BANK_QUERY_TAB, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildBankQueryTab);
    OPCODE( SMSG_GUILD_BANK_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GUILD_BANK_SWAP_ITEMS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildBankSwapItems);
    OPCODE( CMSG_GUILD_BANK_BUY_TAB, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildBankBuyTab);
    OPCODE( CMSG_GUILD_BANK_UPDATE_TAB, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildBankUpdateTab);
    OPCODE( CMSG_GUILD_BANK_DEPOSIT_MONEY, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankDepositMoney);
    OPCODE( CMSG_GUILD_BANK_WITHDRAW_MONEY, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankWithdrawMoney);
    OPCODE( MSG_GUILD_BANK_LOG_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildBankLogQuery);
    OPCODE( CMSG_SET_CHANNEL_WATCH, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetChannelWatch);
    OPCODE( SMSG_USERLIST_ADD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_USERLIST_REMOVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_USERLIST_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CLEAR_CHANNEL_WATCH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_INSPECT_TALENT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GOGOGO_OBSOLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ECHO_PARTY_SQUELCH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_TITLE_SUFFIX, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SPELLCLICK, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSpellClick);
    OPCODE( SMSG_LOOT_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_CHARACTER_RESTORE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GM_CHARACTER_SAVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_VOICESESSION_FULL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_GUILD_PERMISSIONS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildPermissions);
    OPCODE( MSG_GUILD_BANK_MONEY_WITHDRAWN, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleGuildBankMoneyWithdrawn);
    OPCODE( MSG_GUILD_EVENT_LOG_QUERY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGuildEventLogQueryOpcode);
    OPCODE( CMSG_MAELSTROM_RENAME_GUILD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GET_MIRRORIMAGE_DATA, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleMirrrorImageDataRequest);
    OPCODE( SMSG_MIRRORIMAGE_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_FORCE_DISPLAY_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPELL_CHANCE_RESIST_PUSHBACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_IGNORE_DIMINISHING_RETURNS_CHEAT, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_NULL);
    OPCODE( SMSG_IGNORE_DIMINISHING_RETURNS_CHEAT, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_KEEP_ALIVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_EarlyProccess);
    OPCODE( SMSG_RAID_READY_CHECK_ERROR, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_OPT_OUT_OF_LOOT, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleOptOutOfLootOpcode);
    OPCODE( MSG_QUERY_GUILD_BANK_TEXT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQueryGuildBankTabText);
    OPCODE( CMSG_SET_GUILD_BANK_TEXT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetGuildBankTabText);
    OPCODE( CMSG_SET_GRANTABLE_LEVELS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_GRANT_LEVEL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_REFER_A_FRIEND, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_DECLINE_CHANNEL_INVITE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleChannelDeclineInvite);
    OPCODE( CMSG_DECLINE_CHANNEL_INVITE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_GROUPACTION_THROTTLED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_OVERRIDE_LIGHT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_TOTEM_CREATED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_TOTEM_DESTROYED, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTotemDestroyed);
    OPCODE( CMSG_EXPIRE_RAID_INSTANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_NO_SPELL_VARIANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_QUESTGIVER_STATUS_MULTIPLE_QUERY, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleQuestgiverStatusMultipleQuery);
    OPCODE( SMSG_QUESTGIVER_STATUS_MULTIPLE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_PLAYER_DECLINED_NAMES, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetPlayerDeclinedNames);
    OPCODE( SMSG_SET_PLAYER_DECLINED_NAMES_RESULT, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUERY_SERVER_BUCK_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CLEAR_SERVER_BUCK_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SERVER_BUCK_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SEND_UNLEARN_SPELLS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PROPOSE_LEVEL_GRANT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ACCEPT_LEVEL_GRANT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_REFER_A_FRIEND_FAILURE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_SET_FLYING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_UNSET_FLYING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SUMMON_CANCEL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHANGE_PERSONAL_ARENA_RATING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_ALTER_APPEARANCE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleAlterAppearance);
    OPCODE( SMSG_ENABLE_BARBER_SHOP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BARBER_SHOP_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CALENDAR_GET_CALENDAR, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarGetCalendar);
    OPCODE( CMSG_CALENDAR_GET_EVENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarGetEvent);
    OPCODE( CMSG_CALENDAR_GUILD_FILTER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarGuildFilter);
    OPCODE( CMSG_CALENDAR_ARENA_TEAM, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarArenaTeam);
    OPCODE( CMSG_CALENDAR_ADD_EVENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarAddEvent);
    OPCODE( CMSG_CALENDAR_UPDATE_EVENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarUpdateEvent);
    OPCODE( CMSG_CALENDAR_REMOVE_EVENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarRemoveEvent);
    OPCODE( CMSG_CALENDAR_COPY_EVENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarCopyEvent);
    OPCODE( CMSG_CALENDAR_EVENT_INVITE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarEventInvite);
    OPCODE( CMSG_CALENDAR_EVENT_RSVP, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarEventRsvp);
    OPCODE( CMSG_CALENDAR_EVENT_REMOVE_INVITE, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarEventRemoveInvite);
    OPCODE( CMSG_CALENDAR_EVENT_STATUS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarEventStatus);
    OPCODE( CMSG_CALENDAR_EVENT_MODERATOR_STATUS, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarEventModeratorStatus);
    OPCODE( SMSG_CALENDAR_SEND_CALENDAR, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_SEND_EVENT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_FILTER_GUILD, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_ARENA_TEAM, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_INVITE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_INVITE_REMOVED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_COMMAND_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_RAID_LOCKOUT_ADDED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_RAID_LOCKOUT_REMOVED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_INVITE_ALERT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_INVITE_REMOVED_ALERT, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_INVITE_STATUS_ALERT, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_REMOVED_ALERT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_UPDATED_ALERT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_EVENT_MODERATOR_STATUS_ALERT, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CALENDAR_COMPLAIN, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCalendarComplain);
    OPCODE( CMSG_CALENDAR_GET_NUM_PENDING, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleCalendarGetNumPending);
    OPCODE( SMSG_CALENDAR_SEND_NUM_PENDING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SAVE_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_NOTIFY_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PLAY_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_PLAY_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LOAD_DANCES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_STOP_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_STOP_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SYNC_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_DANCE_QUERY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_DANCE_QUERY_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_INVALIDATE_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_DELETE_DANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_LEARNED_DANCE_MOVES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LEARN_DANCE_MOVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_UNLEARN_DANCE_MOVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_RUNE_COUNT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_RUNE_COOLDOWN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_PITCH_RATE_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( MSG_MOVE_SET_PITCH_RATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_FORCE_PITCH_RATE_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_PITCH_RATE_CHANGE_ACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SPLINE_SET_PITCH_RATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MOVE_ABANDON_TRANSPORT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CALENDAR_UPDATE_INVITE_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CALENDAR_UPDATE_INVITE_LIST2, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_UPDATE_MISSILE_TRAJECTORY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_UPDATE_ACCOUNT_DATA_COMPLETE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_TRIGGER_MOVIE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_COMPLETE_MOVIE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_GLYPH_SLOT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_GLYPH, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_ACHIEVEMENT_EARNED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_DYNAMIC_DROP_ROLL_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CRITERIA_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUERY_INSPECT_ACHIEVEMENTS, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleQueryInspectAchievements);
    OPCODE( SMSG_RESPOND_INSPECT_ACHIEVEMENTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_DISMISS_CONTROLLED_VEHICLE, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleDismissControlledVehicle);
    OPCODE( CMSG_COMPLETE_ACHIEVEMENT_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    //OPCODE( CMSG_TRACKED_ACHIEVEMENT_UPDATE, STATUS_NEVER, PROCESS_INPLACE, &WorldSession::Handle_NULL); DA SOSTITUIRE A COMPLETE_ACHIEVEMENT_CHEAT IN FUTURO
    OPCODE( SMSG_QUESTUPDATE_ADD_PVP_KILL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_CRITERIA_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CALENDAR_UPDATE_INVITE_LIST3, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_UNITANIMTIER_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CHAR_CUSTOMIZE, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCharCustomize);
    OPCODE( SMSG_CHAR_CUSTOMIZE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_RENAMEABLE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REQUEST_VEHICLE_EXIT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRequestVehicleExit);
    OPCODE( CMSG_REQUEST_PLAYER_VEHICLE_EXIT, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleRequestVehicleExit);
    OPCODE( CMSG_REQUEST_VEHICLE_PREV_SEAT, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleChangeSeatsOnControlledVehicle);
    OPCODE( CMSG_REQUEST_VEHICLE_NEXT_SEAT, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleChangeSeatsOnControlledVehicle);
    OPCODE( CMSG_REQUEST_VEHICLE_SWITCH_SEAT, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleChangeSeatsOnControlledVehicle);
    OPCODE( CMSG_PET_LEARN_TALENT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandlePetLearnTalent);
    OPCODE( CMSG_PET_UNLEARN_TALENTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SET_PHASE_SHIFT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ALL_ACHIEVEMENT_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_SAY_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_HEALTH_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_POWER_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GAMEOBJ_REPORT_USE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGameobjectReportUse);
    OPCODE( SMSG_HIGHEST_THREAT_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_THREAT_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_THREAT_REMOVE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_THREAT_CLEAR, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CONVERT_RUNE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_RESYNC_RUNES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ADD_RUNE_POWER, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_START_QUEST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_REMOVE_GLYPH, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleRemoveGlyph);
    OPCODE( CMSG_DUMP_OBJECTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_DUMP_OBJECTS_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_DISMISS_CRITTER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleDismissCritter);
    OPCODE( SMSG_NOTIFY_DEST_LOC_SPELL_CAST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_AUCTION_LIST_PENDING_SALES, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleAuctionListPendingSales);
    OPCODE( SMSG_AUCTION_LIST_PENDING_SALES, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MODIFY_COOLDOWN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_UPDATE_COMBO_POINTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ENABLETAXI, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleTaxiQueryAvailableNodes);
    OPCODE( SMSG_PRE_RESURRECT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AURA_UPDATE_ALL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_AURA_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FLOOD_GRACE_CHEAT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SERVER_FIRST_ACHIEVEMENT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_LEARNED_SPELL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PET_REMOVED_SPELL, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleChangeSeatsOnControlledVehicle);
    OPCODE( CMSG_HEARTH_AND_RESURRECT, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleHearthAndResurrect);
    OPCODE( SMSG_ON_CANCEL_EXPECTED_RIDE_VEHICLE_AURA, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CRITERIA_DELETED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ACHIEVEMENT_DELETED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SERVER_INFO_QUERY, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SERVER_INFO_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHECK_LOGIN_CRITERIA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_SERVER_BUCK_DATA_START, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_QUERY_VEHICLE_STATUS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_BATTLEGROUND_INFO_THROTTLED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_PLAYER_VEHICLE_DATA, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_PLAYER_VEHICLE_ENTER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleEnterPlayerVehicle);
    OPCODE( CMSG_EJECT_PASSENGER, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleEjectPassenger);
    OPCODE( SMSG_PET_GUIDS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_CLIENTCACHE_VERSION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ITEM_REFUND_INFO_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_ITEM_REFUND_INFO, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleItemRefundInfoRequest);
    OPCODE( CMSG_ITEM_REFUND, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleItemRefund);
    OPCODE( SMSG_ITEM_REFUND_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CORPSE_MAP_POSITION_QUERY, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleCorpseMapPositionQuery);
    OPCODE( SMSG_CORPSE_MAP_POSITION_QUERY_RESPONSE, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LFG_SET_ROLES_2, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_CALENDAR_CONTEXT_EVENT_SIGNUP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CALENDAR_ACTION_PENDING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_EQUIPMENT_SET_LIST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_EQUIPMENT_SET_SAVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleEquipmentSetSave);
    OPCODE( CMSG_UPDATE_PROJECTILE_POSITION, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleUpdateProjectilePosition);
    OPCODE( SMSG_SET_PROJECTILE_POSITION, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_TALENTS_INFO, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_LEARN_PREVIEW_TALENTS, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleLearnPreviewTalents);
    OPCODE( CMSG_LEARN_PREVIEW_TALENTS_PET, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleLearnPreviewTalentsPet);
    OPCODE( SMSG_ARENA_OPPONENT_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_ARENA_TEAM_CHANGE_FAILED_QUEUED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_MULTIPLE_PACKETS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_FORCE_UNK1_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_UNK1_SPEED_CHANGE_ACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_FORCE_UNK2_SPEED_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_FORCE_UNK2_SPEED_CHANGE_ACK, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_MOVE_LEVITATING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_UNKNOWN_1235, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SPLINE_MOVE_UNKNOWN_1236, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_EQUIPMENT_SET_USE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleEquipmentSetUse);
    OPCODE( SMSG_EQUIPMENT_SET_USE_RESULT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_UNKNOWN_1240, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHAR_FACTION_CHANGE, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCharFactionOrRaceChange);
    OPCODE( SMSG_CHAR_FACTION_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEFIELD_MGR_ENTRY_INVITE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEFIELD_MGR_ENTRY_INVITE_RESPONSE, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_NULL);
    OPCODE( SMSG_BATTLEFIELD_MGR_ENTERED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEFIELD_MGR_QUEUE_INVITE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEFIELD_MGR_QUEUE_INVITE_RESPONSE, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_NULL);
    OPCODE( CMSG_BATTLEFIELD_MGR_QUEUE_REQUEST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_BATTLEFIELD_MGR_QUEUE_REQUEST_RESPONSE, STATUS_NEVER,
            PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEFIELD_MGR_EJECT_PENDING, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_BATTLEFIELD_MGR_EJECTED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_BATTLEFIELD_MGR_EXIT_REQUEST, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_BATTLEFIELD_MGR_STATE_CHANGE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( MSG_SET_RAID_DIFFICULTY, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleSetRaidDifficultyOpcode);
    OPCODE( SMSG_TOGGLE_XP_GAIN, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GMRESPONSE_DB_ERROR, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_GMRESPONSE_RECEIVED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GMRESPONSE_RESOLVE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleGMResponseResolve);
    OPCODE( SMSG_GMRESPONSE_STATUS_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_WORLD_STATE_UI_TIMER_UPDATE, STATUS_LOGGEDIN,
            PROCESS_THREADUNSAFE, &WorldSession::HandleWorldStateUITimerUpdate);
    OPCODE( SMSG_WORLD_STATE_UI_TIMER_UPDATE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_CHAR_RACE_CHANGE, STATUS_AUTHED, PROCESS_THREADUNSAFE,
            &WorldSession::HandleCharFactionOrRaceChange);
    OPCODE( SMSG_TALENTS_INVOLUNTARILY_RESET, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_UNKNOWN_1276, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LOOT_SLOT_CHANGED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_READY_FOR_ACCOUNT_DATA_TIMES, STATUS_AUTHED,
            PROCESS_THREADUNSAFE,
            &WorldSession::HandleReadyForAccountDataTimes);
    OPCODE( CMSG_QUERY_QUESTS_COMPLETED, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleQueryQuestsCompleted);
    OPCODE( SMSG_QUERY_QUESTS_COMPLETED_RESPONSE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_GM_REPORT_LAG, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE,
            &WorldSession::HandleReportLag);
    OPCODE( SMSG_CORPSE_NOT_IN_INSTANCE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_SET_ALLOW_LOW_LEVEL_RAID1, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( CMSG_SET_ALLOW_LOW_LEVEL_RAID2, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_CAMERA_SHAKE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_UPDATE_ITEM_ENCHANTMENTS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_REDIRECT_CLIENT, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REDIRECTION_FAILED, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_UNKNOWN_1295, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_UNKNOWN_1296, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_FORCE_SEND_QUEUED_PACKETS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REDIRECTION_AUTH_PROOF, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_COMBAT_LOG_MULTIPLE, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_LFG_OPEN_FROM_GOSSIP, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_UNKNOWN_1302, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_UNKNOWN_1303, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE( SMSG_UNKNOWN_1304, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( SMSG_SEND_QUEUED_PACKETS, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_ServerSide);
    OPCODE( CMSG_REDIRECT_AUTH_PROOF, STATUS_NEVER, PROCESS_INPLACE,
            &WorldSession::Handle_NULL);
    OPCODE(CMSG_AUTO_DECLINE_GUILD_INVITES, STATUS_NEVER, PROCESS_INPLACE, &WorldSession::Handle_NULL);
    OPCODE(CMSG_SET_PRIMARY_TALENT_TREE, STATUS_NEVER, PROCESS_INPLACE, &WorldSession::Handle_NULL);
    OPCODE(CMSG_GROUP_SET_ROLES, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE, &WorldSession::HandleGroupSetRoles);
    OPCODE(CMSG_GUILD_QUERY_NEWS, STATUS_LOGGEDIN, PROCESS_INPLACE, &WorldSession::HandleGuildQueryNews);
    OPCODE(SMSG_UNKNOWN_1310, STATUS_NEVER, PROCESS_INPLACE, &WorldSession::Handle_ServerSide);
    OPCODE(CMSG_RETURN_TO_GRAVEYARD, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE, &WorldSession::HandleMoveToGraveyard);
    OPCODE(CMSG_REFORGE, STATUS_LOGGEDIN, PROCESS_THREADUNSAFE, &WorldSession::HandleReforgeOpcode);
    OPCODE(CMSG_COMPLETED_ARTIFACTS, STATUS_LOGGEDIN, PROCESS_INPLACE, &WorldSession::HandleCompletedArtifactsOpcode);
}
;
