/*
 * Copyright (C) 2010 - 2012 ProjectSkyfire <http://www.projectskyfire.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2008 - 2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_ROGUE and SPELLFAMILY_GENERIC spells used by rogue players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_rog_".
 */

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"

enum RogueSpells {
	ROGUE_SPELL_SHIV_TRIGGERED = 5940,
	ROGUE_SPELL_GLYPH_OF_PREPARATION = 56819,
	ROGUE_SPELL_PREY_ON_THE_WEAK = 58670,
};

// Cheat Death
class spell_rog_cheat_death: public SpellScriptLoader {
public:
	spell_rog_cheat_death() :
			SpellScriptLoader("spell_rog_cheat_death") {
	}

	class spell_rog_cheat_death_AuraScript: public AuraScript {
		PrepareAuraScript(spell_rog_cheat_death_AuraScript)
		;

		uint32 absorbChance;

		enum Spell {
			ROG_SPELL_CHEAT_DEATH_COOLDOWN = 31231,
		};

		bool Validate(SpellEntry const * /*spellEntry*/) {
			return sSpellStore.LookupEntry(ROG_SPELL_CHEAT_DEATH_COOLDOWN);
		}

		bool Load() {
			absorbChance = SpellMgr::CalculateSpellEffectAmount(GetSpellProto(),
					EFFECT_0);
			return GetUnitOwner()->ToPlayer();
		}

		void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount,
				bool & canBeRecalculated) {
			// Set absorbtion amount to unlimited
			amount = -1;
		}

		void Absorb(AuraEffect * aurEff, DamageInfo & dmgInfo,
				uint32 & absorbAmount) {
			Unit * target = GetTarget();
			if (dmgInfo.GetDamage() < target->GetHealth())
				return;
			if (target->ToPlayer()->HasSpellCooldown(
					ROG_SPELL_CHEAT_DEATH_COOLDOWN))
				return;
			if (!roll_chance_i(absorbChance))
				return;

			target->CastSpell(target, ROG_SPELL_CHEAT_DEATH_COOLDOWN, true);
			target->ToPlayer()->AddSpellCooldown(ROG_SPELL_CHEAT_DEATH_COOLDOWN,
					0, time(NULL) + 60);

			uint32 health10 = target->CountPctFromMaxHealth(10);

			// hp > 10% - absorb hp till 10%
			if (target->GetHealth() > health10)
				absorbAmount = dmgInfo.GetDamage() - target->GetHealth()
						+ health10;
			// hp lower than 10% - absorb everything
			else
				absorbAmount = dmgInfo.GetDamage();
		}

		void Register() {
			DoEffectCalcAmount +=
					AuraEffectCalcAmountFn(spell_rog_cheat_death_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
			OnEffectAbsorb +=
					AuraEffectAbsorbFn(spell_rog_cheat_death_AuraScript::Absorb, EFFECT_0);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_rog_cheat_death_AuraScript();
	}
};

// 31130 - Nerves of Steel
class spell_rog_nerves_of_steel: public SpellScriptLoader {
public:
	spell_rog_nerves_of_steel() :
			SpellScriptLoader("spell_rog_nerves_of_steel") {
	}

	class spell_rog_nerves_of_steel_AuraScript: public AuraScript {
		PrepareAuraScript(spell_rog_nerves_of_steel_AuraScript)
		;

		uint32 absorbPct;

		bool Load() {
			absorbPct = SpellMgr::CalculateSpellEffectAmount(GetSpellProto(),
					EFFECT_0, GetCaster());
			return true;
		}

		void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount,
				bool & canBeRecalculated) {
			// Set absorbtion amount to unlimited
			amount = -1;
		}

		void Absorb(AuraEffect * /*aurEff*/, DamageInfo & dmgInfo,
				uint32 & absorbAmount) {
			// reduces all damage taken while stun or fear
			if (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS)
					& (UNIT_FLAG_STUNNED | UNIT_FLAG_FLEEING))
				absorbAmount = CalculatePctN(dmgInfo.GetDamage(), absorbPct);
		}

		void Register() {
			DoEffectCalcAmount +=
					AuraEffectCalcAmountFn(spell_rog_nerves_of_steel_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
			OnEffectAbsorb +=
					AuraEffectAbsorbFn(spell_rog_nerves_of_steel_AuraScript::Absorb, EFFECT_0);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_rog_nerves_of_steel_AuraScript();
	}
};

class spell_rog_preparation: public SpellScriptLoader 
{
public:
	spell_rog_preparation() : SpellScriptLoader("spell_rog_preparation") 
    { }

	class spell_rog_preparation_SpellScript: public SpellScript 
    {
		PrepareSpellScript(spell_rog_preparation_SpellScript)
		bool Validate(SpellEntry const * /*spellEntry*/) 
        {
			if (!sSpellStore.LookupEntry(ROGUE_SPELL_GLYPH_OF_PREPARATION))
				return false;
			return true;
		}

		void HandleDummy(SpellEffIndex /*effIndex*/)
        {
			Unit *caster = GetCaster();
			if (caster->GetTypeId() != TYPEID_PLAYER)
				return;

            if (Player* rogue = caster->ToPlayer())
            {
                // Sprint
                if (rogue->HasSpellCooldown(2983))
                    rogue->RemoveSpellCooldown(2983, true);

                // Vanish
                if (rogue->HasSpellCooldown(1856))
                    rogue->RemoveSpellCooldown(1856, true);

                // Shadowstep
                if (rogue->HasSpellCooldown(36554))
                    rogue->RemoveSpellCooldown(36554, true);

                // Glyph of preparation
                if (rogue->HasAura(56819))
                {
                    // Kick
                    if (rogue->HasSpellCooldown(1766))
                        rogue->RemoveSpellCooldown(1766, true);

                    // Dismantle
                    if (rogue->HasSpellCooldown(51722))
                        rogue->RemoveSpellCooldown(51722, true);

                    // Smoke bomb
                    if (rogue->HasSpellCooldown(76577))
                        rogue->RemoveSpellCooldown(76577, true);
                }
            }
		}

		void Register() 
        {
			// add dummy effect spell handler to Preparation
			OnEffect += SpellEffectFn(spell_rog_preparation_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript *GetSpellScript() const 
    {
		return new spell_rog_preparation_SpellScript();
	}
};

// 51685-51689 Prey on the Weak
class spell_rog_prey_on_the_weak: public SpellScriptLoader {
public:
	spell_rog_prey_on_the_weak() :
			SpellScriptLoader("spell_rog_prey_on_the_weak") {
	}

	class spell_rog_prey_on_the_weak_AuraScript: public AuraScript {
		PrepareAuraScript(spell_rog_prey_on_the_weak_AuraScript)
		bool Validate(SpellEntry const * /*spellEntry*/) {
			if (!sSpellStore.LookupEntry(ROGUE_SPELL_PREY_ON_THE_WEAK))
				return false;
			return true;
		}

		void HandleEffectPeriodic(AuraEffect const * /*aurEff*/) {
			Unit* pTarget = GetTarget();
			Unit* pVictim = pTarget->getVictim();
			if (pVictim
					&& (pTarget->GetHealthPct() > pVictim->GetHealthPct())) {
				if (!pTarget->HasAura(ROGUE_SPELL_PREY_ON_THE_WEAK)) {
					int32 bp = SpellMgr::CalculateSpellEffectAmount(
							GetSpellProto(), 0);
					pTarget->CastCustomSpell(pTarget,
							ROGUE_SPELL_PREY_ON_THE_WEAK, &bp, 0, 0, true);
				}
			} else
				pTarget->RemoveAurasDueToSpell(ROGUE_SPELL_PREY_ON_THE_WEAK);
		}

		void Register() {
			OnEffectPeriodic +=
					AuraEffectPeriodicFn(spell_rog_prey_on_the_weak_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_rog_prey_on_the_weak_AuraScript();
	}
};

class spell_rog_shiv: public SpellScriptLoader {
public:
	spell_rog_shiv() :
			SpellScriptLoader("spell_rog_shiv") {
	}

	class spell_rog_shiv_SpellScript: public SpellScript {
		PrepareSpellScript(spell_rog_shiv_SpellScript)
		bool Validate(SpellEntry const * /*spellEntry*/) {
			if (!sSpellStore.LookupEntry(ROGUE_SPELL_SHIV_TRIGGERED))
				return false;
			return true;
		}

		void HandleDummy(SpellEffIndex /*effIndex*/) {
			Unit *caster = GetCaster();
			if (caster->GetTypeId() != TYPEID_PLAYER)
				return;

			if (Unit *unitTarget = GetHitUnit())
				caster->CastSpell(unitTarget, ROGUE_SPELL_SHIV_TRIGGERED, true);
		}

		void Register() {
			// add dummy effect spell handler to Shiv
			OnEffect +=
					SpellEffectFn(spell_rog_shiv_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript *GetSpellScript() const {
		return new spell_rog_shiv_SpellScript();
	}
};

class spell_rog_deadly_poison: public SpellScriptLoader {
public:
	spell_rog_deadly_poison() :
			SpellScriptLoader("spell_rog_deadly_poison") {
	}

	class spell_rog_deadly_poison_SpellScript: public SpellScript {
		PrepareSpellScript(spell_rog_deadly_poison_SpellScript)

	private:
		uint8 m_stackAmount;
	public:
		spell_rog_deadly_poison_SpellScript() :
				m_stackAmount(0) {
		}

		void HandleBeforeHit() {
			Player * player = GetCaster()->ToPlayer();
			Unit * target = GetHitUnit();

			if (!player || !target)
				return;

			// Deadly Poison
			if (AuraEffect const * aurEff = target->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_ROGUE, 0x10000, 0x80000, 0, player->GetGUID()))
				m_stackAmount = aurEff->GetBase()->GetStackAmount();
		}

		void HandleAfterHit() {
			if (m_stackAmount < 5)
				return;

			Player * player = GetCaster()->ToPlayer();
			Unit * target = GetHitUnit();
			Item * castItem = GetCastItem();

			if (!player || !target || !castItem)
				return;

			Item * item = player->GetItemByPos(INVENTORY_SLOT_BAG_0,
					EQUIPMENT_SLOT_MAINHAND);

			if (item == castItem)
				item = player->GetItemByPos(INVENTORY_SLOT_BAG_0,
						EQUIPMENT_SLOT_OFFHAND);

			if (!item)
				return;

			// item combat enchantments
			for (uint8 e_slot = 0; e_slot < MAX_ENCHANTMENT_SLOT; ++e_slot) {
				uint32 enchant_id = item->GetEnchantmentId(
						EnchantmentSlot(e_slot));
				SpellItemEnchantmentEntry const * pEnchant =
						sSpellItemEnchantmentStore.LookupEntry(enchant_id);

				if (!pEnchant)
					continue;

				for (uint8 s = 0; s < 3; ++s) {
					if (pEnchant->type[s] != ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL)
						continue;

					SpellEntry const *spellInfo = sSpellStore.LookupEntry(
							pEnchant->spellid[s]);

					if (!spellInfo) {
						sLog->outError(
								"Player::CastItemCombatSpell Enchant %i, cast unknown spell %i",
								pEnchant->ID, pEnchant->spellid[s]);
						continue;
					}

					// Proc only rogue poisons
					if ((spellInfo->SpellFamilyName != SPELLFAMILY_ROGUE)
							|| (spellInfo->Dispel != DISPEL_POISON))
						continue;

					// Do not reproc deadly
					if (spellInfo->SpellFamilyFlags.IsEqual(0x10000, 0x80000,
							0))
						continue;

					if (IsPositiveSpell(pEnchant->spellid[s]))
						player->CastSpell(player, pEnchant->spellid[s], true,
								item);
					else
						player->CastSpell(target, pEnchant->spellid[s], true,
								item);
				}
			}
		}

		void Register() {
			BeforeHit +=
					SpellHitFn(spell_rog_deadly_poison_SpellScript::HandleBeforeHit);
			AfterHit +=
					SpellHitFn(spell_rog_deadly_poison_SpellScript::HandleAfterHit);
		}
	};

	SpellScript * GetSpellScript() const {
		return new spell_rog_deadly_poison_SpellScript();
	}
};

// Vanish bugg (Improved stealth)
class spell_rog_vanish_buff: public SpellScriptLoader 
{
public:
	spell_rog_vanish_buff() : SpellScriptLoader("spell_rog_vanish_buff") 
	{ }

	class spell_rog_vanish_buff_AuraScript: public AuraScript
	{
		PrepareAuraScript(spell_rog_vanish_buff_AuraScript);

		void HandleRemove(AuraEffect const * aurEff, AuraEffectHandleModes mode) 
		{
            if (!GetCaster())
                return;

			if (GetCaster()->ToPlayer())
			{
				if (GetCaster()->ToPlayer()->HasSpellCooldown(1784))
					GetCaster()->ToPlayer()->RemoveSpellCooldown(1784, true);

				GetCaster()->CastSpell(GetCaster(), 1784, true);
			}
		}
		
		void Register()
		{
			OnEffectRemove += AuraEffectRemoveFn(spell_rog_vanish_buff_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
		}
	};

	AuraScript *GetAuraScript() const
	{
		return new spell_rog_vanish_buff_AuraScript();
	}
};

class spell_rogue_blind : public SpellScriptLoader 
{
public:
	spell_rogue_blind() : SpellScriptLoader("spell_rogue_blind") 
    { }

	class spell_rogue_blind_SpellScript: public SpellScript 
    {
		PrepareSpellScript(spell_rogue_blind_SpellScript)

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
			if (Unit *unitTarget = GetHitUnit())
            {
                // Glyph of Blind
                if (GetCaster()->HasAura(91299))
                {
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, unitTarget->GetAura(32409)); // SW:D shall not be removed.
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                }
            }

		}

		void Register()
        {
			OnEffect += SpellEffectFn(spell_rogue_blind_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
		}
	};

	SpellScript* GetSpellScript() const 
    {
		return new spell_rogue_blind_SpellScript();
	}
};

class spell_rog_eviscerate: public SpellScriptLoader 
{
public:
	spell_rog_eviscerate() : SpellScriptLoader("spell_rog_eviscerate") { }

	class spell_rog_eviscerate_SpellScript: public SpellScript 
    {
		PrepareSpellScript(spell_rog_eviscerate_SpellScript)

		void HandleDummy()
        {
			if(GetCaster()->HasAura(14171) || GetCaster()->HasAura(14172))
			{
				uint8 npt = 2;
				if(Aura* rupture = GetTargetUnit()->GetAura(1943))
				{
					if(uint8 cp = GetCaster()->ToPlayer()->GetComboPoints())
					{
						uint8 p;
						if(GetCaster()->HasAura(14172))
							p = (rand()%5)+1;
						else
							p = (rand()%10)-4;
						if(p /  (6 - cp) >=1)
						rupture->RefreshDuration();
					}
				}
			}
		}

		void Register() 
        {
			OnHit += SpellHitFn(spell_rog_eviscerate_SpellScript::HandleDummy);
		}
	};

	SpellScript *GetSpellScript() const 
    {
		return new spell_rog_eviscerate_SpellScript();
	}
};

void AddSC_rogue_spell_scripts() {
	new spell_rog_cheat_death();
	new spell_rog_nerves_of_steel();
	new spell_rog_preparation();
	new spell_rog_prey_on_the_weak();
	new spell_rog_shiv();
	new spell_rog_deadly_poison();
	new spell_rog_vanish_buff();
    new spell_rogue_blind();
	new spell_rog_eviscerate();
}
